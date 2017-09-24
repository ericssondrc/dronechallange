package szoftverhurkak

import gnu.io.CommPortIdentifier
import gnu.io.SerialPort
import java.io.IOException
import java.io.InputStream
import java.io.PrintWriter

class ArduinoCommunicator(private val instructionCompiler: InstructionCompiler) {

    @Volatile
    private var stopped = false
    private var printWriter: PrintWriter? = null
    private var readerThread: Thread? = null
    var commandExecutionListener: (String) -> Unit = {}

    fun connect(commPort: String, baudRate: Int) {
        stopped = false
        val portId = CommPortIdentifier.getPortIdentifier(commPort)
        val serialPort = portId.open("Drone Controller", 5000) as SerialPort

        serialPort.setSerialPortParams(
                baudRate,
                SerialPort.DATABITS_8,
                SerialPort.STOPBITS_1,
                SerialPort.PARITY_NONE)

        printWriter = PrintWriter(serialPort.outputStream)
        readerThread = Thread(ReaderThread(serialPort.inputStream)).apply { start() }
    }

    fun sendInstruction(instruction: Instruction) {
        printWriter?.write(instructionCompiler.compile(instruction))
        printWriter?.flush()
    }

    fun sendInstructions(instructions: List<Instruction>) {
        printWriter?.write(instructionCompiler.compile(instructions))
        printWriter?.flush()
    }

    private inner class ReaderThread(private val inputStream: InputStream) : Runnable {
        override fun run() {
            val stringBuilder = StringBuilder()
            while (!stopped) {
                try {
                    var i = inputStream.read()
                    while (i != -1) {
                        stringBuilder.append(i.toChar())
                        i = inputStream.read()
                    }
                    if (stringBuilder.isNotEmpty()) {
                        commandExecutionListener(stringBuilder.toString())
                        stringBuilder.delete(0, stringBuilder.length)
                    }
                } catch (e: IOException) {
                    e.printStackTrace()
                }
            }
            Thread.interrupted()
        }

    }

    fun stop() {
        stopped = true
        readerThread?.interrupt()
        printWriter?.close()
    }
}
