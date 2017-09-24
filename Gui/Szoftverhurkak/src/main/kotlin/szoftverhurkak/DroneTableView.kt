package szoftverhurkak

import javafx.beans.property.Property
import javafx.collections.FXCollections
import javafx.event.ActionEvent
import javafx.event.EventHandler
import javafx.geometry.Pos
import javafx.scene.control.Button
import javafx.scene.control.ComboBox
import javafx.scene.control.TableView
import javafx.scene.control.TextField
import javafx.scene.layout.GridPane
import tornadofx.*

class InstructionModel {
    constructor(order: Number, channel1: Number, channel2: Number, channel3: Number, channel4: Number, time: Number) {
        this.order = order
        this.channel1 = channel1
        this.channel2 = channel2
        this.channel3 = channel3
        this.channel4 = channel4
        this.time = time
    }

    var order by property<Number>()
    fun orderProperty() = getProperty(InstructionModel::order)

    var channel1 by property<Number>()
    fun channel1Property() = getProperty(InstructionModel::channel1)

    var channel2 by property<Number>()
    fun channel2Property() = getProperty(InstructionModel::channel2)

    var channel3 by property<Number>()
    fun channel3Property() = getProperty(InstructionModel::channel3)

    var channel4 by property<Number>()
    fun channel4Property() = getProperty(InstructionModel::channel4)

    var time by property<Number>()
    fun timeProperty() = getProperty(InstructionModel::time)

    fun toInstructon() = Instruction(channel1.toInt(), channel2.toInt(), channel3.toInt(), channel4.toInt(), time.toInt())
}

class InstructionViewModel : ItemViewModel<InstructionModel>() {
    val order: Property<Number> = bind { item?.orderProperty() }
    val channel1: Property<Number> = bind { item?.channel1Property() }
    val channel2: Property<Number> = bind { item?.channel2Property() }
    val channel3: Property<Number> = bind { item?.channel3Property() }
    val channel4: Property<Number> = bind { item?.channel4Property() }
    val time: Property<Number> = bind { item?.timeProperty() }
}

val connectionManager = ConnectionManager()
var communicator: ArduinoCommunicator? = null


class DroneTableView : View() {
    override val root = GridPane()

    private val tableContent = FXCollections.observableArrayList<InstructionModel>()
    private val viewModel: InstructionViewModel by inject()

    private lateinit var tableView: TableView<InstructionModel>
    private lateinit var connectButton: Button
    private lateinit var disconnectButton: Button
    private lateinit var stepButton: Button
    private lateinit var runButton: Button
    private lateinit var comboBox: ComboBox<String>
    private lateinit var baudRateTextField: TextField

    private var orderCounter = 1
    private var commPort: String? = null

    override fun onDelete() {
        super.onDelete()
    }

    private fun connectClicked() {
        try {
            communicator = connectionManager.connect(commPort, baudRateTextField.text?.toInt())
            communicator?.commandExecutionListener = { println(it) }
            connectButton.isDisable = true
            disconnectButton.isDisable = false
            comboBox.isDisable = true
            baudRateTextField.isDisable = true
            runButton.isDisable = false
            stepButton.isDisable = false
        } catch (e: Exception) {
            println(e.message)
        }
    }

    private fun disconnectClicked() {
        connectionManager.disconnect()
        disconnectButton.isDisable = true
        connectButton.isDisable = false
        comboBox.isDisable = false
        baudRateTextField.isDisable = false
        runButton.isDisable = true
        stepButton.isDisable = true
    }

    init {
        with(root) {
            hbox {
                vbox {
                    label("Instructions for the copter")
                    tableView = tableview(tableContent) {
                        column("Order", InstructionModel::orderProperty)
                        column("Channel 1", InstructionModel::channel1Property)
                        column("Channel 2", InstructionModel::channel2Property)
                        column("Channel 3", InstructionModel::channel3Property)
                        column("Channel 4", InstructionModel::channel4Property)
                        column("Time (ms)", InstructionModel::timeProperty)
                    }
                }
                vbox {
                    hbox {
                        alignment = Pos.CENTER
                        vbox {
                            label("Comm port")
                            comboBox = combobox(values = connectionManager.getCommPorts()) {
                                onAction = EventHandler<ActionEvent> { commPort = selectedItem }
                            }
                        }
                        vbox {
                            label("Baud rate")
                            baudRateTextField = textfield("9600")
                        }
                        vbox {
                            label("")
                            hbox {
                                connectButton = button("Connect") {
                                    action {
                                        connectClicked()
                                    }
                                }
                                disconnectButton = button("Disconnect") {
                                    isDisable = true
                                    action {
                                        disconnectClicked()
                                    }
                                }
                            }
                        }
                    }

                    form {
                        fieldset("Instruction") {
                            field("Channel 1") {
                                textfield(viewModel.channel1) {
                                    promptText = "Hossztengely"
                                }
                            }
                            field("Channel 2") {
                                textfield(viewModel.channel2) {
                                    promptText = "Kereszttengely"
                                }
                            }
                            field("Channel 3") {
                                textfield(viewModel.channel3) {
                                    promptText = "Függőleges (emelkedés)"
                                }
                            }
                            field("Channel 4") {
                                textfield(viewModel.channel4) {
                                    promptText = "Oldalkormány"
                                }
                            }
                            field("Time") {
                                textfield(viewModel.time) {
                                    required()
                                    promptText = "ms"
                                }
                            }
                        }
                        button("Add Instruction") {
                            alignment = Pos.CENTER
                            action {
                                viewModel.commit {
                                    tableContent.add(InstructionModel(
                                            orderCounter++,
                                            viewModel.channel1.value ?: 1520,
                                            viewModel.channel2.value ?: 1520,
                                            viewModel.channel3.value ?: 1520,
                                            viewModel.channel4.value ?: 1520,
                                            viewModel.time.value))
                                }
                            }
                        }
                        button("Remove Instruction") {
                            action {
                                tableContent.remove(tableView.selectedItem)
                            }
                        }
                    }

                    hbox {
                        alignment = Pos.CENTER
                        stepButton = button("Step") {
                            isDisable = true
                            action {
                                action {
                                    tableView.selectedItem?.let {
                                        communicator?.sendInstruction(it.toInstructon())
                                    }
                                }
                            }
                        }
                        runButton = button("Run") {
                            isDisable = true
                            action {
                                communicator?.sendInstructions(tableContent.map { it.toInstructon() })
                            }
                        }
                        button("Save") {

                        }
                        button("Clear") {
                            action {
                                tableContent.clear()
                                orderCounter = 1
                            }
                        }
                        button("Load") {

                        }
                    }
                }
            }
        }
    }

}