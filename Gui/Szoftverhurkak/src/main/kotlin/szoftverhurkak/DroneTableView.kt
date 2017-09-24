package szoftverhurkak

import javafx.beans.property.Property
import javafx.collections.FXCollections
import javafx.collections.ObservableList
import javafx.event.ActionEvent
import javafx.event.EventHandler
import javafx.geometry.Pos
import javafx.scene.control.Button
import javafx.scene.control.TableView
import javafx.scene.control.TextField
import javafx.scene.layout.GridPane
import tornadofx.*
import tornadofx.Stylesheet.Companion.button

val tableContent = FXCollections.observableArrayList<Instruction>()


class Instruction {
    constructor(channel1: Number, channel2: Number, channel3: Number, channel4: Number, time: Number) {
        this.channel1 = channel1
        this.channel2 = channel2
        this.channel3 = channel3
        this.channel4 = channel4
        this.time = time
    }

    var channel1 by property<Number>()
    fun channel1Property() = getProperty(Instruction::channel1)

    var channel2 by property<Number>()
    fun channel2Property() = getProperty(Instruction::channel2)

    var channel3 by property<Number>()
    fun channel3Property() = getProperty(Instruction::channel3)

    var channel4 by property<Number>()
    fun channel4Property() = getProperty(Instruction::channel4)

    var time by property<Number>()
    fun timeProperty() = getProperty(Instruction::time)

    override fun toString(): String = "$channel1;$channel2;$channel3;$channel4;$time"
}

class InstructionModel : ItemViewModel<Instruction>() {
    val channel1: Property<Number> = bind { item?.channel1Property() }
    val channel2: Property<Number> = bind { item?.channel2Property() }
    val channel3: Property<Number> = bind { item?.channel3Property() }
    val channel4: Property<Number> = bind { item?.channel4Property() }
    val time: Property<Number> = bind { item?.timeProperty() }
}

val connectionManager = ConnectionManager()

//val arduinoCommunicator = object : ArduinoCommunicator("COM4") {
//    override fun onMessageReceived(command: String) {
//        println("returned command: $command")
//    }
//}


class DroneTableView : View() {
    override val root = GridPane()

    val model: InstructionModel by inject()
    var runButton: Button? = null
    var commPort: String? = null
    var currentPosition = 0

    override fun onDelete() {
//        arduinoCommunicator.stop()
        super.onDelete()
    }

    init {
        with(root) {
            hbox {
                vbox {
                    label("Instructions for the copter")
                    tableview(tableContent) {
                        column("Channel 1", Instruction::channel1Property)
                        column("Channel 2", Instruction::channel2Property)
                        column("Channel 3", Instruction::channel3Property)
                        column("Channel 4", Instruction::channel4Property)
                        column("Time (ms)", Instruction::timeProperty)

                        onSelectionChange {
                            colorpicker { }
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
                                        connectionManager.connect(commPort, baudRateTextField?.text?.toInt())
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
                                textfield(model.channel1)
                            }
                            field("Channel 2") {
                                textfield(model.channel2)
                            }
                            field("Channel 3") {
                                textfield(model.channel3)
                            }
                            field("Channel 4") {
                                textfield(model.channel4)
                            }
                            field("Time") {
                                textfield(model.time).required()
                            }
                        }
                        button {
                            alignment = Pos.CENTER
                            text = "Add Instruction"
                            action {
                                model.commit {
                                    tableContent.add(Instruction(
                                            model.channel1.value ?: 1500,
                                            model.channel2.value ?: 1500,
                                            model.channel3.value ?: 1500,
                                            model.channel4.value ?: 1500,
                                            model.time.value))
                                }
                            }
                        }
                    }

                    hbox {
                        alignment = Pos.CENTER
                        runButton = button("Run") {
                            action {
                                val message = tableContent.subList(currentPosition, tableContent.size).joinToString("|")
//                                arduinoCommunicator.sendString(message)
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
                    }
                }
            }
        }
    }

}