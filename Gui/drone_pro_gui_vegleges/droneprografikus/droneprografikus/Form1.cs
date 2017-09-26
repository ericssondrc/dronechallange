using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Threading;
using System.Windows.Forms;
using System.IO.Ports;
using System.Diagnostics;

namespace droneprografikus
{
    public partial class Form1 : Form
    {
        int sdb = 0;
        int sdb2 = 1;
        const int height = 20;
        public void ujsor()
        {
            CheckBox cb = new CheckBox();
            cb.Location = new Point(0, (panel1.Controls.Count >= 5) ? panel1.Controls[panel1.Controls.Count - 5].Top+ height: 0);
            cb.Width = 35;
            cb.Name = "cb_" + sdb;
            panel1.Controls.Add(cb);
            NumericUpDown nu = new NumericUpDown();
            nu.Height = 20;
            nu.Width = 54;
            nu.Location = new Point(40, (panel1.Controls.Count >=5)?panel1.Controls[panel1.Controls.Count - 5].Top+height:0);//sdb * nu.Height);
            nu.Minimum = 1;
            nu.Maximum = 4;
            nu.Name = "nu_" + sdb + "_1";
            nu.Leave += Nu_Leave;
            if (sdb2 != 1) panel1.Controls["nu_" + (sdb2 - 2) + "_1"].Leave -= Nu_Leave;
            nu.Leave += Nu_Leave1;
            panel1.Controls.Add(nu);
            nu = new NumericUpDown();
            nu.Height = 20;
            nu.Width = 44;
            nu.Location = new Point(94, (panel1.Controls.Count >= 5) ? panel1.Controls[panel1.Controls.Count - 5].Top+height : 0);
            nu.Minimum = 1000;
            nu.Maximum = 2000;
            nu.Name = "nu_" + sdb + "_2";
            panel1.Controls.Add(nu);
            nu = new NumericUpDown();
            nu.Width = 63;
            nu.Height = 20;
            nu.Location = new Point(138, (panel1.Controls.Count >= 5) ? panel1.Controls[panel1.Controls.Count - 5].Top+height : 0);
            nu.Minimum = 0;
            nu.Maximum = 100000;
            nu.Name = "nu_" + sdb + "_3";
            panel1.Controls.Add(nu);
            Button bt = new Button();
            bt.Width = 30;
            bt.Height = 20;
            bt.Location = new Point(201, (panel1.Controls.Count >= 5) ? panel1.Controls[panel1.Controls.Count - 5].Top +height: 0);
            bt.Click += Bt_Click;
            bt.Name = "bt_" + sdb;
            bt.Visible = false;
            panel1.Controls.Add(bt);
            sdb++; sdb2++;
        }
        public void rewrite()
        {
            foreach (var a in Directory.GetFiles("saves\\"))
            {
                Button x = new Button();
                x.Name = a.Split('.')[0].Substring(a.Split('.')[0].LastIndexOf('\\') + 1);
                x.Text = x.Name.ToString();
                x.Width = keszek.Width;
                x.Height = 20;
                x.Top = keszek.Controls.Count * 20;
                x.Click += X_Click;
                List<int[]> tomb = new List<int[]>();
                StreamReader sr = new StreamReader(a);
                string b = "";
                while (!sr.EndOfStream)
                {
                    b = sr.ReadLine();
                    tomb.Add(new int[3]);
                    for (int q = 0; q < 3; q++)
                        tomb[tomb.Count - 1][q] = Convert.ToInt32(b.Split(',')[q]);
                }
                sr.Close();
                x.Tag = tomb;
                keszek.Controls.Add(x);
            }
        }

        public void atrendez()//Martin
        {
            Control.ControlCollection gombok = keszek.Controls;
            int q = 0;
            foreach (var item in gombok)
            {
                (item as Button).Top = q * (item as Button).Height;
                q++;
            }
        }
        private void Nu_Leave1(object sender, EventArgs e)
        {
            int y = Convert.ToInt32((sender as NumericUpDown).Name.Split('_')[1]);
            (panel1.Controls["cb_" + y] as CheckBox).Checked = true;
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string[] a = SerialPort.GetPortNames();
            for (int i = 0; i < a.Length; i++)
            {
                comboBox1.Items.Add(a[i].ToString());
            }
            if (a.Length != 0) comboBox1.SelectedItem = comboBox1.Items[0];

            // foreach (var item in Directory.GetFiles("saves\\"))
            {
                // textBox1.Text = item.Split('.')[0];
                rewrite();

            }
            for (int i = 0; i < 10; i++)
            {
                ujsor();
            }
            pictureBox1.Top = 0; pictureBox1.Left = 0;//Martin
            pictureBox1.Width = this.Width;
            pictureBox1.Height = this.Height;
        }

        private void Nu_Leave(object sender, EventArgs e)
        {
            ujsor();
        }

        private void Bt_Click(object sender, EventArgs e)
        {

        }


        private void startbt_Click(object sender, EventArgs e)
        {
            //StreamWriter sw = new StreamWriter(File.Create(@"C:\Users\Lackó\Desktop\adatok.txt"));
            serialPort1.PortName = comboBox1.SelectedItem.ToString();
            serialPort1.Open();

            string sv = "";
            for (int i = 0; i < sdb; i++)
            {
                sv = "";
                if ((panel1.Controls["cb_" + i] as CheckBox).Checked == true)
                {
                    for (int j = 1; j <= 2; j++)
                    {
                        sv += (panel1.Controls["nu_" + i + "_" + j] as NumericUpDown).Value.ToString();
                        sv += ",";
                    }
                    sv += '.';
                }

                serialPort1.Write(sv);
                Thread.Sleep((int)(panel1.Controls["nu_" + i + "_3"] as NumericUpDown).Value);
            }


            //sw.Write(sv);
            //sw.Close();
            serialPort1.Close();
        }

        private void savechecked_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "")
            { MessageBox.Show("Nincs név megadva!"); return; }
            else
            {
                Button x = new Button();
                x.Width = keszek.Width;
                x.Height = 20;
                x.Top = keszek.Controls.Count * 20;
                x.Text = textBox1.Text;
                x.Name = x.Text;
                x.Click += X_Click;
                keszek.Controls.Add(x);
                List<int[]> tomb = new List<int[]>();
                StreamWriter sw = new StreamWriter("saves\\" + x.Text + ".txt");
                for (int i = 0; i < sdb; i++)
                {
                    if ((panel1.Controls["cb_" + i] as CheckBox).Checked == true)
                    {
                        tomb.Add(new int[3]);
                        for (int j = 1; j <= 3; j++)
                        {
                            tomb[tomb.Count - 1][j - 1] = (int)(panel1.Controls["nu_" + i + "_" + j] as NumericUpDown).Value;
                            sw.Write(tomb[tomb.Count - 1][j - 1] + ",");
                        }
                        sw.WriteLine();
                    }
                }
                sw.Close();
                x.Tag = tomb;
            }
        }

        private void X_Click(object sender, EventArgs e)
        {
            DialogResult dr = MessageBox.Show("Ha folytatja, a képernyőn levő kód el fog veszni. Folytatja?", "Figyelmeztetés", MessageBoxButtons.YesNo);
            if (dr == DialogResult.Yes)
            {
                textBox1.Text = (sender as Button).Text;
                sdb = 0; sdb2 = 1;
                panel1.Controls.Clear();
                List<int[]> tomb = ((sender as Button).Tag as List<int[]>);
                for (int i = 0; i < tomb.Count; i++)
                {
                    ujsor();
                    for (int j = 1; j < 4; j++)
                    {

                        (panel1.Controls["nu_" + i + "_" + j] as NumericUpDown).Value = tomb[i][j - 1];
                    }
                }
            }
        }

        private void checkall_CheckedChanged(object sender, EventArgs e)
        {
            for (int i = 0; i < sdb; i++)
            {
                (panel1.Controls["cb_" + i] as CheckBox).Checked = checkall.Checked;
            }
        }

        private void delete_Click(object sender, EventArgs e)
        {
            DialogResult dr = MessageBox.Show("Ha folytatja, ez az utasítássorozat el fog veszni. Folytatja?", "Figyelmeztetés", MessageBoxButtons.YesNo);
            if (dr == DialogResult.Yes)
            {
                File.Delete("saves\\" + textBox1.Text + ".txt");
                keszek.Controls.Remove(keszek.Controls[textBox1.Text] as Button);
                textBox1.Text = "";
                atrendez();       //Martin: gombok törlés utáni igazítása, atrendez fv.
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Process.Start(@"Readme.txt");
        }

        private void button1_MouseHover(object sender, EventArgs e)//Martin
        {
            pictureBox1.Visible = true;
        }

        private void button1_MouseLeave(object sender, EventArgs e)//Martin
        {
            pictureBox1.Visible = false;
        }
    }
}
