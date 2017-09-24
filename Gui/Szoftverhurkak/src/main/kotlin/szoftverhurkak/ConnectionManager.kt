package szoftverhurkak

import gnu.io.CommPortIdentifier

class ConnectionManager {

    private var isConnected = false
    private val instructionCompiler = SemicolonPipeInstructionCompiler()
    private val arduinoCommunicator: ArduinoCommunicator = ArduinoCommunicator(instructionCompiler)

    fun getCommPorts(): List<String> {
        val portIdentifiers = CommPortIdentifier.getPortIdentifiers()
        val commPorts = portIdentifiers.toList().map { it as CommPortIdentifier }
        return commPorts.map { it.name }
//        return listOf("COM1", "COM2", "COM3")
    }

    fun connect(commPort: String?, baudRate: Int?): ArduinoCommunicator {
        if (!isConnected) {
            if (commPort == null || baudRate == null) {
                throw Exception("CommPort ($commPort) and BaudRate ($baudRate) cannot be null.")
            }
            try {
                arduinoCommunicator.connect(commPort, baudRate)
            } catch (e: Exception) {
                throw Exception("Failed to connect on port $commPort with baud rate $baudRate. Cause: ${e.message}", e)
            }
            isConnected = true
        }
        return arduinoCommunicator
    }

    fun disconnect() {
        if (isConnected) {
            arduinoCommunicator.stop()
        }
    }


}