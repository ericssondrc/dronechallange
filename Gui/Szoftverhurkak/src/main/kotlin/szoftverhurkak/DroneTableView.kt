package szoftverhurkak

import javafx.beans.property.Property
import javafx.collections.FXCollections
import javafx.event.ActionEvent
import javafx.event.EventHandler
import javafx.geometry.Pos
import javafx.scene.control.Button
import javafx.scene.control.TextField
import javafx.scene.layout.GridPane
import tornadofx.*

val tableContent = FXCollections.observableArrayList<InstructionModel>()

class InstructionModel {
    constructor(channel1: Number, channel2: Number, channel3: Number, channel4: Number, time: Number) {
        this.channel1 = channel1
        this.channel2 = channel2
        this.channel3 = channel3
        this.channel4 = channel4
        this.time = time
    }

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

    private val viewModel: InstructionViewModel by inject()
    var runButton: Button? = null
    var commPort: String? = null
    var currentPosition = 0

    override fun onDelete() {
        super.onDelete()
    }

    init {
        with(root) {
            hbox {
                vbox {
                    label("Instructions for the copter")
                    tableview(tableContent) {
                        column("Channel 1", InstructionModel::channel1Property)
                        column("Channel 2", InstructionModel::channel2Property)
                        column("Channel 3", InstructionModel::channel3Property)
                        column("Channel 4", InstructionModel::channel4Property)
                        column("Time (ms)", InstructionModel::timeProperty)

                        onSelectionChange {

                        }
                    }
                }
                vbox {
                    hbox {
                        var baudRateTextField: TextField? = null
                        alignment = Pos.CENTER
                        vbox {
                            label("Comm port")
                            combobox(values = connectionManager.getCommPorts()) {
                                onAction = EventHandler<ActionEvent> { commPort = selectedItem }
                            }
                        }
                        vbox {
                            label("Baud rate")
                            baudRateTextField = textfield("9600")
                        }
                        vbox {
                            label("")
                            button("Connect") {
                                action {
                                    try {
                                        communicator = connectionManager.connect(commPort, baudRateTextField?.text?.toInt())
                                        communicator?.commandExecutionListener = { println(it) }
                                        runButton?.isDisable = false
                                        isDisable = true
                                    } catch (e: Exception) {
                                        println(e.message)
                                    }
                                }
                            }
                        }
                    }

                    form {
                        fieldset("Instruction") {
                            field("Channel 1") {
                                textfield(viewModel.channel1)
                            }
                            field("Channel 2") {
                                textfield(viewModel.channel2)
                            }
                            field("Channel 3") {
                                textfield(viewModel.channel3)
                            }
                            field("Channel 4") {
                                textfield(viewModel.channel4)
                            }
                            field("Time") {
                                textfield(viewModel.time).required()
                            }
                        }
                        button {
                            alignment = Pos.CENTER
                            text = "Add Instruction"
                            action {
                                viewModel.commit {
                                    tableContent.add(InstructionModel(
                                            viewModel.channel1.value ?: 1520,
                                            viewModel.channel2.value ?: 1520,
                                            viewModel.channel3.value ?: 1520,
                                            viewModel.channel4.value ?: 1520,
                                            viewModel.time.value))
                                }
                            }
                        }
                    }

                    hbox {
                        alignment = Pos.CENTER
                        runButton = button("Run") {
                            action {
                                val instructions = tableContent.subList(currentPosition, tableContent.size)
                                communicator?.sendInstructions(instructions.map { it.toInstructon() })
                                currentPosition = tableContent.size
                            }
                            isDisable = true
                        }
                        button("Save") {

                        }
                        button("Clear") {
                            action {
                                tableContent.clear()
                                currentPosition = 0
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