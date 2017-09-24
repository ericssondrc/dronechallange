package szoftverhurkak

import gnu.io.CommPortIdentifier
import gnu.io.SerialPort
import java.io.IOException
import java.io.InputStream
import java.io.OutputStream
import java.io.PrintWriter

class ArduinoCommunicator(private val instructionCompiler: InstructionCompiler) {

    @Volatile
    private var stopped = false
    private var outStream: OutputStream? = null
    private var readerThread: Thread? = null
    var commandExecutionListener: (String) -> Unit = {}

    fun connect(commPort: String, baudRate: Int) {
        val portId = CommPortIdentifier.getPortIdentifier(commPort)
        val serialPort = portId.open("Drone Controller", 5000) as SerialPort

        serialPort.setSerialPortParams(
                baudRate,
                SerialPort.DATABITS_8,
                SerialPort.STOPBITS_1,
                SerialPort.PARITY_NONE)

        outStream = serialPort.outputStream
        val inStream = serialPort.inputStream

        readerThread = Thread(ReaderThread(inStream))
        readerThread?.start()
    }

    fun sendInstructions(instructions: List<Instruction>) {
        val pw = PrintWriter(outStream)
        pw.write(instructionCompiler.compile(instructions))
        pw.flush()
    }

    private inner class ReaderThread(private val `is`: InputStream) : Runnable {
        override fun run() {
            val stringBuilder = StringBuilder()
            while (!stopped) {
                try {
                    var i = `is`.read()
                    while (i != -1) {
                        stringBuilder.append(i.toChar())
                        i = `is`.read()
                    }
                    if (stringBuilder.isNotEmpty()) {
                        commandExecutionListener(stringBuilder.toString())
                        stringBuilder.delete(0, stringBuilder.length)
                    }
                } catch (e: IOException) {
                    e.printStackTrace()
                }
            }
        }

    }

    fun stop() {
        stopped = true
        readerThread?.interrupt()
    }
}
