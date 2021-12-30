using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.ExceptionServices;
using System.Runtime.InteropServices;
using System.Security;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace OthelloReversi
{
    public partial class Form1 : Form
    {
        private Othello _board;
        public Form1()
        {
            InitializeComponent();
            _board = new Othello(false);
            Draw();
            foreach (Control space in this.tableLayoutPanel1.Controls)
            {
                space.MouseClick += new MouseEventHandler(button_Click);
            }

        }

        void Draw()
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (_board[i,j] == 0)
                    {
                        tableLayoutPanel1.GetControlFromPosition(i, j).BackColor
                            = Color.FromArgb(223, 230, 233);
                    }
                    else if (_board[i, j] == 1)
                    {
                        tableLayoutPanel1.GetControlFromPosition(i, j).BackColor
                            = Color.FromArgb(45, 52, 54);
                    }
                    else if (_board.IsCellAccessible(i,j))
                    {
                        tableLayoutPanel1.GetControlFromPosition(i, j).BackColor
                            = Color.FromArgb(247, 143, 179);
                    }
                    else
                    {
                        tableLayoutPanel1.GetControlFromPosition(i, j).BackColor = Color.Pink;
                    }

                }
            }
        }

        private void button_Click(object sender, EventArgs e)
        {
            Button btn = sender as Button;
            if (btn != null)
            {
                int column =  tableLayoutPanel1.GetColumn(sender as Control);
                int row =  tableLayoutPanel1.GetRow(sender as Control);
                if (!_board.IsValidStep(column,row))
                {
                    MessageBox.Show("Step is not valid!!!");
                    return;
                }
                //MessageBox.Show(column + " " + row);
                _board.MakeStep(column, row);
                Draw();
                (int i, int j) index = _board.MakeComputerStep();
                Task.Factory.StartNew(
                    () =>
                    {                        
                        Thread.Sleep(1000);
                        tableLayoutPanel1.GetControlFromPosition(index.i, index.j).BackColor
                         = Color.FromArgb(214, 48, 49);
                        Thread.Sleep(1000);
                        _board.MakeStep(index.i, index.j);
                        Draw();
                    }
                    );
                
            }
        }
    }
}
