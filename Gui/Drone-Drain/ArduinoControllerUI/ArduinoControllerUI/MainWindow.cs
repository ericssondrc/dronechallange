using Gtk;
using System.IO.Ports;

public partial class MainWindow: Window
{
    private readonly SerialPort serialPort;

    public MainWindow()
        : base(WindowType.Toplevel)
    {
        Build();

        string[] ports = SerialPort.GetPortNames();
        serialPort = new SerialPort
            {
                PortName = ports[4],
                BaudRate = 9600,
                Parity = Parity.None,
                DataBits = 8,
                StopBits = StopBits.One,
                Handshake = Handshake.None,
                ReadTimeout = 500,
                WriteTimeout = 500
            };
        serialPort.Open();
    }

    ~MainWindow()
    {
        serialPort.Close();
    }

    protected void OnDeleteEvent(object sender, DeleteEventArgs a)
    {
        Application.Quit();
        a.RetVal = true;
    }

    protected void OnBtnForwardClicked(object sender, System.EventArgs e)
    {
        serialPort.Write("Forward");
    }

    protected void OnBtnBackwardClicked(object sender, System.EventArgs e)
    {
        serialPort.Write("Backward");
    }

    protected void OnBtnLeftClicked(object sender, System.EventArgs e)
    {
        serialPort.Write("Left");
    }

    protected void OnBtnRightClicked(object sender, System.EventArgs e)
    {
        serialPort.Write("Right");
    }

    protected void OnBtnResetClicked(object sender, System.EventArgs e)
    {
        serialPort.Write("Reset");
    }

    protected void OnBtnUpClicked(object sender, System.EventArgs e)
    {
        serialPort.Write("Up");
    }

    protected void OnBtnTurnLeftClicked(object sender, System.EventArgs e)
    {
        serialPort.Write("TurnLeft");
    }

    protected void OnBtnTurnRightClicked(object sender, System.EventArgs e)
    {
        serialPort.Write("TurnRight");
    }

    protected void OnBtnDownClicked(object sender, System.EventArgs e)
    {
        serialPort.Write("Down");
    }

    protected void OnBtnSendClicked(object sender, System.EventArgs e)
    {
        var values = $"{(int)nudMoveValue.Value};{(int)nudMoveInterval.Value};{(int)nudSmoothValue.Value};{(int)nudSmoothInterval.Value};{(int)nudBrakeValue.Value};{(int)nudBrakeInterval.Value};{(int)nudBrakeSmoothValue.Value};{(int)nudBrakeSmoothInterval.Value}";
        serialPort.Write(values);
    }
}
