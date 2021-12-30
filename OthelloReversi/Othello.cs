using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace OthelloReversi
{
    public class Othello 
    {
        private IntPtr _state;
        private int _dimension;
        private char _availableSymb;

        [DllImport("Othello.dll",EntryPoint = "create_state")]
        static private extern IntPtr create_state(bool curr);

        [DllImport("Othello.dll", EntryPoint = "init_state")]
        static private extern IntPtr init_state(bool curr);

        [DllImport("Othello.dll", EntryPoint = "get_state_field")]
        [return: MarshalAs(UnmanagedType.U1)]
        static private extern char get_state_field(IntPtr state, [MarshalAs(UnmanagedType.I4)] int i, [MarshalAs(UnmanagedType.I4)] int j);

        [DllImport("Othello.dll", EntryPoint = "get_dimension")]
        static private extern int get_dimension();

        [DllImport("Othello.dll", EntryPoint = "is_valid_step")]
        static private extern bool is_valid_step(IntPtr state, int i, int j);

        [DllImport("Othello.dll", EntryPoint = "make_step")]
        static private extern void make_step(IntPtr state, int i, int j);

        [DllImport("Othello.dll", EntryPoint = "make_computer_step")]
        static private extern int make_computer_step(IntPtr state);

        [DllImport("Othello.dll", EntryPoint = "is_game_end")]
        static private extern int is_game_end(IntPtr state);

        [DllImport("Othello.dll", EntryPoint = "get_available_symbol")]
        static private extern char get_available_step_symb();
        public Othello(bool current)
        {
            _state = init_state(false);
            _dimension = get_dimension();
            _availableSymb = get_available_step_symb();
        }
        public int Dimension
        {
            get 
            {
                return _dimension;
            }
        }
        public char AvailableSymb
        {
            get
            {
                return _availableSymb;
            }
        }
        public bool IsValidStep(int i, int j)
        {
            return is_valid_step(_state,i, j);
        }

        public void MakeStep(int i,int j)
        {
            make_step(_state, i, j);
        }

        public (int i,int j) MakeComputerStep()
        {
            int step = make_computer_step(_state);
            (int, int) res = (step / Dimension, step % Dimension);
            return res;
        }
        /// <summary>
        /// true - blacks won
        /// false - whites won
        /// </summary>
        /// <returns></returns>
        public (bool isEnd,bool winner) IsGameEnd()
        {
            int isWin = is_game_end(_state);
            return (isWin!=0,isWin>0);
        }
        public char this[int i,int j]
        {
            get
            {
                return get_state_field(_state, i, j);
            }
        }
        public bool IsCellAccessible(int i,int j)
        {
            return this[i, j] == AvailableSymb;
        }
    }
}
