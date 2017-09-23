namespace droneprografikus
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.panel1 = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.savechecked = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.sorok = new System.Windows.Forms.Panel();
            this.keszek = new System.Windows.Forms.Panel();
            this.label5 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.startbt = new System.Windows.Forms.Button();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.COM = new System.Windows.Forms.Label();
            this.checkall = new System.Windows.Forms.CheckBox();
            this.delete = new System.Windows.Forms.Button();
            this.label7 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // serialPort1
            // 
            this.serialPort1.BaudRate = 115200;
            this.serialPort1.PortName = "COM5";
            // 
            // panel1
            // 
            this.panel1.AutoScroll = true;
            this.panel1.Location = new System.Drawing.Point(17, 103);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(234, 315);
            this.panel1.TabIndex = 0;
            this.panel1.Paint += new System.Windows.Forms.PaintEventHandler(this.panel1_Paint);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(57, 87);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(48, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "csatorna";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(111, 87);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(38, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "kitérés";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(155, 87);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(57, 13);
            this.label3.TabIndex = 3;
            this.label3.Text = "késleltetés";
            // 
            // savechecked
            // 
            this.savechecked.Location = new System.Drawing.Point(17, 61);
            this.savechecked.Name = "savechecked";
            this.savechecked.Size = new System.Drawing.Size(48, 23);
            this.savechecked.TabIndex = 0;
            this.savechecked.Text = "Save";
            this.savechecked.UseVisualStyleBackColor = true;
            this.savechecked.Click += new System.EventHandler(this.savechecked_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(218, 87);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(33, 13);
            this.label4.TabIndex = 4;
            this.label4.Text = "ctrl+c";
            this.label4.Visible = false;
            // 
            // sorok
            // 
            this.sorok.AutoScroll = true;
            this.sorok.Location = new System.Drawing.Point(315, 127);
            this.sorok.Name = "sorok";
            this.sorok.Size = new System.Drawing.Size(200, 131);
            this.sorok.TabIndex = 5;
            // 
            // keszek
            // 
            this.keszek.AutoScroll = true;
            this.keszek.Location = new System.Drawing.Point(315, 320);
            this.keszek.Name = "keszek";
            this.keszek.Size = new System.Drawing.Size(199, 98);
            this.keszek.TabIndex = 6;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(312, 111);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(33, 13);
            this.label5.TabIndex = 7;
            this.label5.Text = "ctrl+v";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(71, 63);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(126, 20);
            this.textBox1.TabIndex = 8;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(312, 304);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(62, 13);
            this.label6.TabIndex = 9;
            this.label6.Text = "kész kódok";
            // 
            // startbt
            // 
            this.startbt.Location = new System.Drawing.Point(315, 63);
            this.startbt.Name = "startbt";
            this.startbt.Size = new System.Drawing.Size(75, 23);
            this.startbt.TabIndex = 10;
            this.startbt.Text = "start";
            this.startbt.UseVisualStyleBackColor = true;
            this.startbt.Click += new System.EventHandler(this.startbt_Click);
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "COM1",
            "COM2",
            "COM3",
            "COM4",
            "COM5",
            "COM6"});
            this.comboBox1.Location = new System.Drawing.Point(440, 62);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(56, 21);
            this.comboBox1.TabIndex = 11;
            // 
            // COM
            // 
            this.COM.AutoSize = true;
            this.COM.Location = new System.Drawing.Point(437, 44);
            this.COM.Name = "COM";
            this.COM.Size = new System.Drawing.Size(31, 13);
            this.COM.TabIndex = 12;
            this.COM.Text = "COM";
            // 
            // checkall
            // 
            this.checkall.AutoSize = true;
            this.checkall.Location = new System.Drawing.Point(18, 87);
            this.checkall.Name = "checkall";
            this.checkall.Size = new System.Drawing.Size(15, 14);
            this.checkall.TabIndex = 13;
            this.checkall.UseVisualStyleBackColor = true;
            this.checkall.CheckedChanged += new System.EventHandler(this.checkall_CheckedChanged);
            // 
            // delete
            // 
            this.delete.Location = new System.Drawing.Point(203, 61);
            this.delete.Name = "delete";
            this.delete.Size = new System.Drawing.Size(48, 23);
            this.delete.TabIndex = 16;
            this.delete.Text = "Del";
            this.delete.UseVisualStyleBackColor = true;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(138, 24);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(0, 13);
            this.label7.TabIndex = 17;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(533, 436);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.delete);
            this.Controls.Add(this.checkall);
            this.Controls.Add(this.COM);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.startbt);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.keszek);
            this.Controls.Add(this.sorok);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.savechecked);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.panel1);
            this.Name = "Form1";
            this.ShowIcon = false;
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button savechecked;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Panel sorok;
        private System.Windows.Forms.Panel keszek;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button startbt;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Label COM;
        private System.Windows.Forms.CheckBox checkall;
        private System.Windows.Forms.Button delete;
        private System.Windows.Forms.Label label7;
    }
}

