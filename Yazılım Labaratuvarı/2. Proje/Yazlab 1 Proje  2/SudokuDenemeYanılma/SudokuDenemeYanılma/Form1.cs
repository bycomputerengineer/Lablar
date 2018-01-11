using System;
using System.Threading;
using System.IO;
using System.Diagnostics;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SudokuDenemeYanılma
{
    public partial class Form1 : Form
    {
        int[,,] sudoku = new int[10, 9, 9];
        Thread thread1;
        Thread thread2;
        Thread thread3;
        Thread thread4;
        Thread thread5;
        Thread thread6;
        Thread thread7;
        Thread thread8;
        Thread thread9;
        Stopwatch sure = new Stopwatch();
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Control.CheckForIllegalCrossThreadCalls = false;
        }

        private void dosyaAçToolStripMenuItem_Click(object sender, EventArgs e)
        {

            String sudo;
            int sayac = 0;
            int i, j;
            for (i = 0; i < 9; i++)
            {
                for (j = 0; j < 9; j++)
                {
                    sudoku[0, i, j] = 0;
                }
            }
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "Text Dosyası|*.txt";
            ofd.ShowDialog();

            try
            {
                FileStream dosya = new FileStream(ofd.FileName, FileMode.Open, FileAccess.Read);
                StreamReader reader = new StreamReader(dosya);
                sudo = reader.ReadToEnd();
                sudo = sudo.Replace('*', ' ');

                for (i = 0; i < 9; i++)
                {
                    for (j = 0; j < 9; j++)
                    {
                        if (sudo[sayac] != ' ')
                        {
                            sudoku[0, i, j] = (int)Char.GetNumericValue(sudo[sayac]);
                        }
                        sayac++;
                    }
                    sayac += 2;
                }
                dosya.Close();

                for (i = 1; i < 10; i++)
                {
                    matrisKopyala(i);
                }

                sudokuYazdır(sudo);
                button1.Enabled = true;
            }
            catch (Exception)
            {
                //bos...
            }
        }

        void matrisKopyala(int a)
        {
            int i,j;
            for(i = 0; i < 9; i++){
                for(j = 0; j < 9; j++){
                    sudoku[a, i, j] = sudoku[0, i, j];
                }
            }
        }
        public void sudokuYazdır(String sudo)
        {
            label1.Text = sudo[0].ToString();
            label2.Text = sudo[1].ToString();
            label3.Text = sudo[2].ToString();
            label4.Text = sudo[3].ToString();
            label5.Text = sudo[4].ToString();
            label6.Text = sudo[5].ToString();
            label7.Text = sudo[6].ToString();
            label8.Text = sudo[7].ToString();
            label9.Text = sudo[8].ToString();
            label10.Text = sudo[11].ToString();
            label11.Text = sudo[12].ToString();
            label12.Text = sudo[13].ToString();
            label13.Text = sudo[14].ToString();
            label14.Text = sudo[15].ToString();
            label15.Text = sudo[16].ToString();
            label16.Text = sudo[17].ToString();
            label17.Text = sudo[18].ToString();
            label18.Text = sudo[19].ToString();
            label19.Text = sudo[22].ToString();
            label20.Text = sudo[23].ToString();
            label21.Text = sudo[24].ToString();
            label22.Text = sudo[25].ToString();
            label23.Text = sudo[26].ToString();
            label24.Text = sudo[27].ToString();
            label25.Text = sudo[28].ToString();
            label26.Text = sudo[29].ToString();
            label27.Text = sudo[30].ToString();
            label28.Text = sudo[33].ToString();
            label29.Text = sudo[34].ToString();
            label30.Text = sudo[35].ToString();
            label31.Text = sudo[36].ToString();
            label32.Text = sudo[37].ToString();
            label33.Text = sudo[38].ToString();
            label34.Text = sudo[39].ToString();
            label35.Text = sudo[40].ToString();
            label36.Text = sudo[41].ToString();
            label37.Text = sudo[44].ToString();
            label38.Text = sudo[45].ToString();
            label39.Text = sudo[46].ToString();
            label40.Text = sudo[47].ToString();
            label41.Text = sudo[48].ToString();
            label42.Text = sudo[49].ToString();
            label43.Text = sudo[50].ToString();
            label44.Text = sudo[51].ToString();
            label45.Text = sudo[52].ToString();
            label46.Text = sudo[55].ToString();
            label47.Text = sudo[56].ToString();
            label48.Text = sudo[57].ToString();
            label49.Text = sudo[58].ToString();
            label50.Text = sudo[59].ToString();
            label51.Text = sudo[60].ToString();
            label52.Text = sudo[61].ToString();
            label53.Text = sudo[62].ToString();
            label54.Text = sudo[63].ToString();
            label55.Text = sudo[66].ToString();
            label56.Text = sudo[67].ToString();
            label57.Text = sudo[68].ToString();
            label58.Text = sudo[69].ToString();
            label59.Text = sudo[70].ToString();
            label60.Text = sudo[71].ToString();
            label61.Text = sudo[72].ToString();
            label62.Text = sudo[73].ToString();
            label63.Text = sudo[74].ToString();
            label64.Text = sudo[77].ToString();
            label65.Text = sudo[78].ToString();
            label66.Text = sudo[79].ToString();
            label67.Text = sudo[80].ToString();
            label68.Text = sudo[81].ToString();
            label69.Text = sudo[82].ToString();
            label70.Text = sudo[83].ToString();
            label71.Text = sudo[84].ToString();
            label72.Text = sudo[85].ToString();
            label73.Text = sudo[88].ToString();
            label74.Text = sudo[89].ToString();
            label75.Text = sudo[90].ToString();
            label76.Text = sudo[91].ToString();
            label77.Text = sudo[92].ToString();
            label78.Text = sudo[93].ToString();
            label79.Text = sudo[94].ToString();
            label80.Text = sudo[95].ToString();
            label81.Text = sudo[96].ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            thread1 = new Thread(sudokuÇöz1);
            thread2 = new Thread(sudokuÇöz2);
            thread3 = new Thread(sudokuÇöz3);
            thread4 = new Thread(sudokuÇöz4);
            thread5 = new Thread(sudokuÇöz5);
            thread6 = new Thread(sudokuÇöz6);
            thread7 = new Thread(sudokuÇöz7);
            thread8 = new Thread(sudokuÇöz8);
            thread9 = new Thread(sudokuÇöz9);
            sure.Start();
            thread1.Start();
            thread2.Start();
            thread3.Start();
            thread4.Start();
            thread5.Start();
            thread6.Start();
            thread7.Start();
            thread8.Start();
            thread9.Start();
        }

        void sudokuÇöz1()
        {
            bool durum = senÇöz(0, 0, 1);
            sudokuTamam(false, 1);
            thread2.Abort();
            thread3.Abort();
            thread4.Abort();
            thread5.Abort();
            thread6.Abort();
            thread7.Abort();
            thread8.Abort();
            thread9.Abort();
            thread1.Abort();
        }
        void sudokuÇöz2()
        {
            bool durum = senÇöz(0, 0, 2);
            sudokuTamam(false,2);
            thread3.Abort();
            thread4.Abort();
            thread5.Abort();
            thread6.Abort();
            thread7.Abort();
            thread8.Abort();
            thread9.Abort();
            thread1.Abort();
            thread2.Abort();
        }
        void sudokuÇöz3()
        {
            bool durum = senÇöz(0, 0, 3);
            sudokuTamam(false,3);
            thread2.Abort();
            thread4.Abort();
            thread5.Abort();
            thread6.Abort();
            thread7.Abort();
            thread8.Abort();
            thread9.Abort();
            thread1.Abort();
            thread3.Abort();
        }
        void sudokuÇöz4()
        {
            bool durum = senÇöz(0, 0, 4);
            sudokuTamam(false, 4);
            thread2.Abort();
            thread3.Abort();
            thread5.Abort();
            thread6.Abort();
            thread7.Abort();
            thread8.Abort();
            thread9.Abort();
            thread1.Abort();
            thread4.Abort();
        }
        void sudokuÇöz5()
        {
            bool durum = senÇöz(0, 0, 5);
            sudokuTamam(false,5);
            thread2.Abort();
            thread3.Abort();
            thread4.Abort();
            thread6.Abort();
            thread7.Abort();
            thread8.Abort();
            thread9.Abort();
            thread1.Abort();
            thread5.Abort();
        }
        void sudokuÇöz6()
        {
            bool durum = senÇöz(0, 0, 6);
            sudokuTamam(false,6);
            thread2.Abort();
            thread3.Abort();
            thread4.Abort();
            thread5.Abort();
            thread7.Abort();
            thread8.Abort();
            thread9.Abort();
            thread1.Abort();
            thread6.Abort();
        }
        void sudokuÇöz7()
        {
            bool durum = senÇöz(0, 0, 7);
            sudokuTamam(false, 7);
            thread2.Abort();
            thread3.Abort();
            thread4.Abort();
            thread5.Abort();
            thread6.Abort();
            thread8.Abort();
            thread9.Abort();
            thread1.Abort();
            thread7.Abort();
        }
        void sudokuÇöz8()
        {
            bool durum = senÇöz(0, 0, 8);
            sudokuTamam(false,8);
            thread2.Abort();
            thread3.Abort();
            thread4.Abort();
            thread5.Abort();
            thread6.Abort();
            thread7.Abort();
            thread9.Abort();
            thread1.Abort();
            thread8.Abort();
        }
        void sudokuÇöz9()
        {
            bool durum = senÇöz(0, 0, 9);
            sudokuTamam(false,9);
            thread2.Abort();
            thread3.Abort();
            thread4.Abort();
            thread5.Abort();
            thread6.Abort();
            thread7.Abort();
            thread8.Abort();
            thread1.Abort();
            thread9.Abort();
        }

        bool senÇöz(int i, int j, int rak)
        {
            int a, b, rakam;
            bool durum = true;
            /*String sudo;

            sudo = stringeAl(sudoku);
            sudokuYazdır(sudo);*/

            for (a = 0; a < 9; a++)
            {
                for (b = 0; b < 9; b++)
                {
                    if (sudoku[rak, a, b] == 0)
                    {
                        durum = false;
                    }
                }
            }
            if (durum == true)
            {
                sudokuTamam(true, rak);
            }
            if (sudoku[rak, i, j] == 0)
            {
                rakam = rak;
                for (/*rakam = 1*/; rakam < 10; rakam++)
                {
                    if (uygunMu(i, j, rakam, rak))
                    {
                        sudoku[rak, i, j] = rakam;
                        if (j < 8)
                        {
                            senÇöz(i, j + 1, rak);
                        }
                        else if (i < 8)
                        {
                            senÇöz(i + 1, 0, rak);
                        }
                        else
                        {
                            sudokuTamam(true, rak);
                        }
                        sudoku[rak, i, j] = 0;
                    }
                    if (rakam == 9)
                    {
                        rakam = -1;
                    }
                    else if (rakam == rak - 1)
                    {
                        break;
                    }
                }
            }
            else
            {
                if (j < 8)
                {
                    senÇöz(i, j + 1, rak);
                }
                else if (i < 8)
                {
                    senÇöz(i + 1, 0, rak);
                }
            }
            return false;
        }

        bool uygunMu(int i, int j, int rakam, int rak)
        {
            bool durum = true;
            int m, n, a, b;
            a = i - (i % 3);
            b = j - (j % 3);
            for (n = 0; n < 9; n++)
            {
                if (sudoku[rak, i, n] == rakam)
                {
                    durum = false;
                    break;
                }
            }
            if (durum == true)
            {
                for (m = 0; m < 9; m++)
                {
                    if (sudoku[rak, m, j] == rakam)
                    {
                        durum = false;
                        break;
                    }
                }
            }
            if (durum == true)
            {
                for (m = a; m < a + 3; m++)
                {
                    for (n = b; n < b + 3; n++)
                    {
                        if (sudoku[rak, m, n] == rakam)
                        {
                            durum = false;
                            break;
                        }
                    }
                    if (durum == false)
                    {
                        break;
                    }
                }
            }
            return durum;
        }

        void sudokuTamam(bool durum, int rak)
        {
            sure.Stop();
            if (durum == true)
            {
                surelabel.Text += sure.ElapsedMilliseconds + "ms";
                String sudo;
                sudo = stringeAl(sudoku, rak);
                sudokuYazdır(sudo);
                sonuc.Text = "Sudoku Çözüldü";
            }
            else
            {
                sonuc.Text = "Sudoku Çözülemedi";
            }
            thread2.Abort();
            thread3.Abort();
            thread4.Abort();
            thread5.Abort();
            thread6.Abort();
            thread7.Abort();
            thread8.Abort();
            thread1.Abort();
            thread9.Abort();
        }

        String stringeAl(int[,,] sudoku, int rak)
        {
            int i, j;
            String sudo = "";
            for (i = 0; i < 9; i++)
            {
                for (j = 0; j < 9; j++)
                {
                    if (sudoku[rak, i, j] != 0)
                    {
                        sudo += sudoku[rak, i, j];
                    }
                    else
                    {
                        sudo += " ";
                    }
                }
                sudo += "  ";
            }
            return sudo;
        }
    }
}
