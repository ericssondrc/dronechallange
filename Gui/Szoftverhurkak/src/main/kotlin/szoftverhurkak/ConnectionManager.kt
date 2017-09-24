package szoftverhurkak

class ConnectionManager {

    private val arduinoCommunicator: ArduinoCommunicator = ArduinoCommunicator()

    fun getCommPorts(): List<String> {
//        val portIdentifiers = CommPortIdentifier.getPortIdentifiers()
//        val commPorts = portIdentifiers.toList().map { it as CommPortIdentifier }
//        return commPorts.map { it.name }
        return listOf("COM1", "COM2")
    }

    fun connect(commPort: String?, baudRate: Int?) {
        val succeeded = arduinoCommunicator.connect(commPort, baudRate)
    }


}