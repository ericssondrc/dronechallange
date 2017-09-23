using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.IO;

namespace droneprografikus
{
    public partial class Form1 : Form
    {
        int sdb = 0;
        int sdb2 = 1;
        public void ujsor()
        {
            CheckBox cb = new CheckBox();
            cb.Location = new Point(0, sdb * 20);
            cb.Width = 35;
            cb.Name = "cb_" + sdb;
            panel1.Controls.Add(cb);
            NumericUpDown nu = new NumericUpDown();
            nu.Height = 20;
            nu.Width = 54;
            nu.Location = new Point(40, sdb * nu.Height);
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
            nu.Location = new Point(94, sdb * nu.Height);
            nu.Minimum = 1000;
            nu.Maximum = 2000;
            nu.Name = "nu_" + sdb + "_2";
            panel1.Controls.Add(nu);
            nu = new NumericUpDown();
            nu.Width = 63;
            nu.Height = 20;
            nu.Location = new Point(138, sdb * nu.Height);
            nu.Minimum = 1;
            nu.Maximum = 100000;
            nu.Name = "nu_" + sdb + "_3";
            panel1.Controls.Add(nu);
            Button bt = new Button();
            bt.Width = 30;
            bt.Height = 20;
            bt.Location = new Point(201, sdb * bt.Height);
            bt.Click += Bt_Click;
            bt.Name = "bt_" + sdb;
            bt.Visible = false;
            panel1.Controls.Add(bt);
            sdb++; sdb2++;
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

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

            for (int i = 0; i < 10; i++)
            {
                ujsor();
            }



        }

        private void Nu_Leave(object sender, EventArgs e)
        {
            ujsor();
        }

        private void Bt_Click(object sender, EventArgs e)
        {

        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void startbt_Click(object sender, EventArgs e)
        {
            StreamWriter sw = new StreamWriter(File.Create(@"C:\Users\Lackó\Desktop\adatok.txt"));
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
                System.Threading.Thread.Sleep((int)(panel1.Controls["nu_" + i + "_3"] as NumericUpDown).Value);
            }
            
            
            sw.Write(sv);
            sw.Close();
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
                x.Click += X_Click;
                keszek.Controls.Add(x);
                List<int[]> tomb = new List<int[]>();
                for (int i = 0; i < sdb; i++)
                {
                    if ((panel1.Controls["cb_" + i] as CheckBox).Checked == true)
                    {
                        tomb.Add(new int[3]);
                        for (int j = 1; j <= 3; j++)
                        {
                            tomb[tomb.Count - 1][j - 1] = (int)(panel1.Controls["nu_" + i + "_" + j] as NumericUpDown).Value;
                        }
                    }
                }
                x.Tag = tomb;
            }
        }

        private void X_Click(object sender, EventArgs e)
        {
            DialogResult dr = MessageBox.Show("Ha folytatja, a képernyőn levő kód el fog veszni. Folytatja?", "Figyelmeztetés", MessageBoxButtons.YesNo);
            if (dr == DialogResult.Yes)
            {
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
    }
}
