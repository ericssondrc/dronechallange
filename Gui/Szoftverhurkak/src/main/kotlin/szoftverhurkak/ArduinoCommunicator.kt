package szoftverhurkak

import gnu.io.*

import java.io.IOException
import java.io.InputStream
import java.io.OutputStream
import java.io.PrintWriter

class ArduinoCommunicator(comPort: String, baudRate: Int = 9600) {

    private val outStream: OutputStream
    @Volatile
    private var stopped = false
    private val readerThread: Thread
    var listener: (String) -> Unit = {}

    init {
        val portId = CommPortIdentifier.getPortIdentifier(comPort)
        val serialPort = portId.open("Demo application", 5000) as SerialPort

        try {
            // Set serial port to 57600bps-8N1..my favourite
            serialPort.setSerialPortParams(
                    baudRate,
                    SerialPort.DATABITS_8,
                    SerialPort.STOPBITS_1,
                    SerialPort.PARITY_NONE)
        } catch (ex: UnsupportedCommOperationException) {
            System.err.println(ex.message)
        }


        outStream = serialPort.outputStream
        val inStream = serialPort.inputStream

        readerThread = Thread(ReaderThread(inStream))
        readerThread.start()
    }

    fun sendString(command: String) {
        val pw = PrintWriter(outStream)
        pw.write(command)
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
                        listener(stringBuilder.toString())
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
        readerThread.interrupt()
    }
}
