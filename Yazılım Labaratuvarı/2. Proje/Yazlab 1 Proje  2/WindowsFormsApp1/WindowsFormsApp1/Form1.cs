using System;
using System.Threading;
using System.IO;
using System.Diagnostics;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        int[,] sudoku = new int[9, 9];
        Thread tred1;
        Thread tred2;
        Thread tred3;

        Form f1 = new Form();
        Form f2 = new Form();
        Form f3 = new Form();

        Stopwatch sure = new Stopwatch();

        FileStream dosya1 = new FileStream("Çözümler/çözüm1.txt", FileMode.Create, FileAccess.Write);
        StreamWriter writer1;
        FileStream dosya2 = new FileStream("Çözümler/çözüm2.txt", FileMode.Create, FileAccess.Write);
        StreamWriter writer2;
        FileStream dosya3 = new FileStream("Çözümler/çözüm3.txt", FileMode.Create, FileAccess.Write);
        StreamWriter writer3;

        public Form1()
        {
            InitializeComponent();
        }

        void Form1_Load(object sender, EventArgs e)
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
                    sudoku[i, j] = 0;
                }
            }
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "Text Dosyası|*.txt";
            ofd.ShowDialog();

           try{
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
                            sudoku[i, j] = (int)Char.GetNumericValue(sudo[sayac]);
                        }
                        sayac++;
                    }
                    sayac += 2;
                }

                dosya.Close();
                sudokuYazdır(sudo);
                button1.Enabled = true;
            }
            catch(Exception)
            {
                //bos...
            }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            sudokuHesapla();
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

        void sudokuHesapla()
        {
            tred1 = new Thread(work1);
            tred2 = new Thread(work2);
            tred3 = new Thread(work3);

            sure.Start();
            tred1.Start();
            tred2.Start();
            tred3.Start();            
        }

        void work1()
        {
            int i, j, sayac;
            bool durum = false;
            int[,] sudoku1 = new int[9, 9];
            writer1 = new StreamWriter(dosya1);
            String sudo = "";

            for (i = 0; i < 9; i++)
            {
                for (j = 0; j < 9; j++)
                {
                    sudoku1[i, j] = sudoku[i,j];
                }
            }

            while (durum == false)/****DURUM FALSE ISE(SUDOKU TAMAMLANMADIYSA)****/
            {
                for (sayac = 0; sayac < 9; sayac++) /********ALAN DOLASIR****/
                {
                    sudoku1 = sikistirma(sayac, sudoku1);///SIKISTIRMAYI DENE///
                    sudoku1 = kesistirme(sayac, sudoku1);///KESISTIRMEYI DENE///
                    sudoku1 = eksikRakam(sayac, sudoku1);///EKSIK RAKAM DENE///
                    sudo = stringeAl(sudoku1);
                    writer1.WriteLine(sudo);
                }

                durum = true;
                for (i = 0; i < 9; i++)/***SUDOKULARI DOLAS****/
                {
                    for (j = 0; j < 9; j++)
                    {
                        if (sudoku1[i, j] == 0)
                        {
                            durum = false;
                        }
                    }
                }
            }
            sure.Stop();
            tred2.Abort();
            tred3.Abort();
            writer1.Close();
            writer2.Close();
            writer3.Close();
            dosya1.Close();
            dosya2.Close();
            dosya3.Close();
            sudokuYazdır(sudo);
            MessageBox.Show("Çözüm bitti!","Bilgi");
            ilkbitiren.Text += "Thread 1";
            cs.Text += sure.ElapsedMilliseconds + " ms";
            button2.Enabled = true;
            tred1.Abort();
        }
        
        void work2()
        {
            int i, j, sayac;
            bool durum = false;
            int[,] sudoku1 = new int[9, 9];
            writer2 = new StreamWriter(dosya2);
            String sudo = "";

            for (i = 0; i < 9; i++)
            {
                for (j = 0; j < 9; j++)
                {
                    sudoku1[i, j] = sudoku[i, j];
                }
            }

            while (durum == false)/****DURUM FALSE ISE(SUDOKU TAMAMLANMADIYSA)****/
            {
                for (sayac = 3; ; sayac++) /********ALAN DOLASIR****/
                {
                    sudoku1 = sikistirma(sayac, sudoku1);///SIKISTIRMAYI DENE///
                    sudoku1 = kesistirme(sayac, sudoku1);///KESISTIRMEYI DENE///
                    sudoku1 = eksikRakam(sayac, sudoku1);///EKSIK RAKAM DENE///
                    if (sayac == 2)
                    {
                        break;
                    }
                    else if (sayac == 8)
                    {
                        sayac = -1;
                    }
                    sudo = stringeAl(sudoku1);
                    writer2.WriteLine(sudo);
                }

                durum = true;
                for (i = 0; i < 9; i++)/***SUDOKULARI DOLAS****/
                {
                    for (j = 0; j < 9; j++)
                    {
                        if (sudoku1[i, j] == 0)
                        {
                            durum = false;
                        }
                    }
                }
            }
            sure.Stop();
            tred1.Abort();
            tred3.Abort();
            writer1.Close();
            writer2.Close();
            writer3.Close();
            dosya1.Close();
            dosya2.Close();
            dosya3.Close();
            sudokuYazdır(sudo);
            MessageBox.Show("Çözüm bitti!", "Bilgi");
            ilkbitiren.Text += "Thread 2";
            cs.Text += sure.ElapsedMilliseconds + " ms";
            button2.Enabled = true;
            tred2.Abort();
        }

        void work3()
        {
            int i, j, sayac;
            bool durum = false;
            int[,] sudoku1 = new int[9, 9];
            writer3 = new StreamWriter(dosya3);
            String sudo = "";

            for (i = 0; i < 9; i++)
            {
                for (j = 0; j < 9; j++)
                {
                    sudoku1[i, j] = sudoku[i, j];
                }
            }

            while (durum == false)/****DURUM FALSE ISE(SUDOKU TAMAMLANMADIYSA)****/
            {
                for (sayac = 6; ; sayac++) /********ALAN DOLASIR****/
                {
                    sudoku1 = sikistirma(sayac, sudoku1);///SIKISTIRMAYI DENE///
                    sudoku1 = kesistirme(sayac, sudoku1);///KESISTIRMEYI DENE///
                    sudoku1 = eksikRakam(sayac, sudoku1);///EKSIK RAKAM DENE///
                    if(sayac == 5)
                    {
                        break;
                    }
                    else if(sayac == 8)
                    {
                        sayac = -1;
                    }
                    sudo = stringeAl(sudoku1);
                    writer3.WriteLine(sudo);
                }

                durum = true;
                for (i = 0; i < 9; i++)/***SUDOKULARI DOLAS****/
                {
                    for (j = 0; j < 9; j++)
                    {
                        if (sudoku1[i, j] == 0)
                        {
                            durum = false;
                        }
                    }
                }
            }
            sure.Stop();
            tred1.Abort();
            tred2.Abort();
            writer1.Close();
            writer2.Close();
            writer3.Close();
            dosya1.Close();
            dosya2.Close();
            dosya3.Close();
            sudokuYazdır(sudo);
            MessageBox.Show("Çözüm bitti!", "Bilgi");
            ilkbitiren.Text += "Thread 3";
            cs.Text += sure.ElapsedMilliseconds + " ms";
            button2.Enabled = true;
            tred3.Abort();
        }

        int[,] kesistirme(int sayac, int[,] sudoku)///HUCREYE GELEBILECEK DEGERLERI BULUR///
        {
            bool[] status = new bool[10];
            int temp = 0;
            int m, n, i, j, a, b, sayi = 0;

            sayi = 0;
            m = sayac - (sayac % 3);
            for (i = m; i < m + 3; i++)/*************ALANDA SATIR DOLASIR****/
            {
                n = (sayac % 3) * 3;
                for (j = n; j < n + 3; j++)/*********ALANDA SUTUN DOLASIR****/
                {
                    if (sudoku[i, j] == 0)/**********ILGILI SATIR VE SUTUNUN KESISIMINDEKI HUCRE BOS ISE****/
                    {
                        for (a = 0; a <= 9; a++)/****HUCREYE GELEBILECEK SAYILARI TRUE YAP*****/
                        {
                            status[a] = true;
                        }

                        for (a = 0; a < 9; a++)/****ILGILI HUCRENIN SATIRINI DOLAS*****/
                        {
                            if (sudoku[i, a] != 0)/****HUCREDEKI DEEGER BOS DEGILSE****/
                            {
                                status[sudoku[i, a]] = false; /***BU DEGERIN ILGILI HUCREYE GELME DURUMUNU FALSE YAP*****/
                            }
                        }
                        for (a = 0; a < 9; a++)/*****ILGILI HUCRENIN SUTUNUNU DOLAS****/
                        {
                            if (sudoku[a, j] != 0)/****HUCREDEKI DEGER BOS DEGILSE*****/
                            {
                                status[sudoku[a, j]] = false;/****BU DEGERIN ILGILI HUCREYE GELME DURUMUNU FALSE YAP*****/
                            }
                        }
                        for (a = m; a < m + 3; a++)/****ILGILI HUCRENIN BULUNDUGU ALANI DOLASIR(ALT FOR ILE BIRLIKTE)****/
                        {
                            for (b = n; b < n + 3; b++)/****ILGILI HUCRENIN BULUNDUGU ALANI DOLASIR(UST FOR ILE BIRLIKTE)*****/
                            {
                                if (sudoku[a, b] != 0)/****HUCREDEKI DEGER BOS DEGILSE*****/
                                {
                                    status[sudoku[a, b]] = false;/****BU DEGERIN ILGILI HUCREYE GELME DURUMUNU FALSE YAP*****/
                                }
                            }
                        }
                        for (a = 1; a <= 9; a++)/****HUCREYE GELEBILECEK DEGERLERIN LISTESINI DOLAS(ILGILI HUCREYE KAC DEGER GELEBILECEGINI TESPIT ETMEK ICIN)******/
                        {
                            if (status[a] == true)/****LISTEDEKI a INDISINDEKI DEGER UHCREYE GELEBILIR ISE****/
                            {
                                sayi++;/****HUCREYE GELEBILECEK DEGERLER SAYISINI BIR ARTTIR*****/
                                temp = a;/****FOR BITTIGINDE HUCREYE GELEBILECEK DEGERLERDEN EN SONUNCUSU KALIR TEMP DEGISKENINDE****/
                            }
                        }
                        if (sayi == 1)/****USTTEKI FOR BITINCE SAYI DEGISKENI BIRSE EDMEKKI O HUCREYE TEK DEGER GELEBILIR****/
                        {
                            sudoku[i, j] = temp;/*****BU DEGER DE YUKRIDAKI FORDA SONUNCU VE TEK DEGER OLARAK TEMPE ATANMISTI. SIMDI O DEGERI AIT OLDUGU LANET YERE KOYUYORUZ*****/
                        }
                    }
                }
            }
            return sudoku;
        }

        int[,] sikistirma(int sayac, int[,] sudoku)///BIR DEGERIN GIDEBILECEGI TEK BIR HUCRE BULMAYA CALISIR///
        {
            Nokta nokta = new Nokta();
            int rakam = 0, sayi;
            bool durum;
            int m, n, i, j, a, b;

            for (rakam = 1; rakam < 10; rakam++)/*****RAKAMLARI TEK TEK DENE****/
                                {
                sayi = 0;
                m = sayac - (sayac % 3);
                for (i = m; i < m + 3; i++)/*************ALANDA SATIR DOLASIR****/
                {
                    n = (sayac % 3) * 3;
                    for (j = n; j < n + 3; j++)/*********ALANDA SUTUN DOLASIR****/
                    {
                        if (sudoku[i, j] == 0)/**********ALANDAKI HUCRE BOS MU?***/
                        {
                            durum = true;
                            for (a = 0; a < 9; a++)/**************SATIRI TARAR****/
                            {
                                if (sudoku[i, a] == rakam)/*******SATIRDA ILGILI RAKAM VAR ISE****/
                                {
                                    durum = false;
                                    break;
                                }
                            }
                            for (a = 0; (a < 9 && durum != false); a++)/******SUTUNU DOLAS******/
                            {
                                if (sudoku[a, j] == rakam)/****SUTUNDA ILGILI RAKAM VAR MI?*****/
                                {
                                    durum = false;
                                    break;
                                }
                            }
                            for (a = m; (a < m + 3 && durum != false); a++)/******ALANI DOLAS(ALTTAKI FORLA BIRLIKTE)****/
                            {
                                for (b = n; b < n + 3; b++)/***********ALANI DOLAS(USTTEKI FORLA BIRLIKTE)*******/
                                {
                                    if (sudoku[a, b] == rakam)/*******HUCREDE ILGILI RAKAM VAR MI********/
                                    {
                                        durum = false;
                                        break;
                                    }
                                }
                            }
                            if (durum == true)/*****RAKAM ARANAN KISIMLARDA YOKSA*******/
                            {
                                sayi++;/************SAYIYI ARTTIR******/
                                if (sayi == 1)/*****SAYI BIRSE KOORDINATLARI KAYDET*********/
                                {
                                    nokta.x = i;
                                    nokta.y = j;
                                }
                            }
                        }
                    }
                }
                if (sayi == 1)/***SAYI HALA BIRSE KAYDEDILEN KORDINATLARA RAKAM DEGERINI YERLESTIR*****/
                {
                    sudoku[nokta.x, nokta.y] = rakam;
                }
            }
            return sudoku;
        }

        int[,] eksikRakam(int sayac, int[,] sudoku)
        {
            int m, n, i, j, a;
            int satirda_bos_hucre_sayisi = 0, sutunda_bos_hucre_sayisi = 0;
            bool[] satir_status = new bool[10];
            bool[] sutun_status = new bool[10];
            Nokta satir_nokta1 = new Nokta();
            Nokta satir_nokta2 = new Nokta();
            Nokta sutun_nokta1 = new Nokta();
            Nokta sutun_nokta2 = new Nokta();
            int satir_eksik1 = 0;
            int satir_eksik2 = 0;
            int sutun_eksik1 = 0;
            int sutun_eksik2 = 0;

            m = sayac - (sayac % 3);
            for (i = m; i < m + 3; i++)///-------Sudokuy alanini dolas------------/////
            {
                n = (sayac % 3) * 3;
                for (j = n; j < n + 3; j++)
                {
                    if(sudoku[i,j] == 0)////--------Eger hucre bossa-------////
                    {
                        for(a = 0; a < 9; a++)/////-----Hucrenin bulundugu satiri dolas------/////
                        {
                            if(sudoku[i, a] == 0)////-------Eger hucre bossa--------////
                            {
                                satirda_bos_hucre_sayisi++;////-------Satirdaki bos hucre sayisini tutan degiskenin degerini bir arttir------////
                                if(satir_nokta1 == null)/////---------Nokta 1 icin daha once deger atanmadiysa koordinatlari nokta 1'e ata------/////
                                {
                                    satir_nokta1.x = i;
                                    satir_nokta1.y = a;
                                }
                                else if(satir_nokta2 == null)/////--------Atandiysa koordinatlari nokta 2'ye ata-------/////
                                {
                                    satir_nokta2.x = i;
                                    satir_nokta2.y = a;
                                }
                            }
                            else{////-----Eger hucre bos degilse -----/////
                                satir_status[sudoku[i, a]] = false; ///// ----Hucredeki deger ile iliskili status degerini false yap------////
                            }
                        }
                        for (a = 0; a < 9; a++)////-------Hucrenin bulundugu sutunu dolas-------/////
                        {
                            if (sudoku[a, j] == 0)////-----Eger hucre bossa --------/////
                            {
                                sutunda_bos_hucre_sayisi++; /////-----Sutundaki bos hucre sayisini tutan degiskeni bir arttir-------/////
                                if (sutun_nokta1 == null)/////----- Eger nokta 1 bos ise koordinatlari nokta1'e ata------/////
                                {
                                    sutun_nokta1.x = a;
                                    sutun_nokta1.y = j;
                                }
                                else if(sutun_nokta2 == null)/////-------Nokta 1 dolu ise nokta 2 bos ise koordinatlari nokta 2'ye ata------////
                                {
                                    sutun_nokta2.x = a;
                                    sutun_nokta2.y = j;
                                }
                            }
                            else////-----Eger hucre bos degilse -----/////
                            {
                                sutun_status[sudoku[a, j]] = false;///// ----Hucredeki deger ile iliskili status degerini false yap------////
                            }
                        }
                        if(satirda_bos_hucre_sayisi == 2)/////-----Satirdaki bos hucre sayisi 2 ise -----/////
                        {
                            for(a = 1; a < 10; a++)/////-----Satiri dolas ve eksik elemanlari bul-------/////
                            {
                                if(satir_status[a] == true)/////-------Satirda a degeri var ise----/////
                                {
                                    if(satir_eksik1 == 0)/////------Birinci eksik elemani tutacak deger bos ise a degerini ona ata-----////
                                    {
                                        satir_eksik1 = a;
                                    }
                                    else if(satir_eksik2 == 0)/////------eger degilse digerine ata------/////
                                    {
                                        satir_eksik2 = a;
                                    }
                                }
                            }
                            for(a = 0; a < 9; a++)/////-----Bos hucrenin bulundugu sutunlari dolas eger eksik elemanlardan herhangi biri bu sutunlarda bulunuyorsa eksik elemanlari uygun sekilde satira yerlestir-------/////
                            {
                                if(sudoku[a,satir_nokta1.y] == satir_eksik1)
                                {
                                    sudoku[satir_nokta1.x, satir_nokta1.y] = satir_eksik2;
                                    sudoku[satir_nokta2.x, satir_nokta2.y] = satir_eksik1;
                                }
                                if(sudoku[a, satir_nokta1.y] == satir_eksik2)
                                {
                                    sudoku[satir_nokta1.x, satir_nokta1.y] = satir_eksik1;
                                    sudoku[satir_nokta2.x, satir_nokta2.y] = satir_eksik2;
                                }
                                if (sudoku[a, satir_nokta2.y] == satir_eksik1)
                                {
                                    sudoku[satir_nokta1.x, satir_nokta1.y] = satir_eksik1;
                                    sudoku[satir_nokta2.x, satir_nokta2.y] = satir_eksik2;
                                }
                                if (sudoku[a, satir_nokta2.y] == satir_eksik2)
                                {
                                    sudoku[satir_nokta1.x, satir_nokta1.y] = satir_eksik2;
                                    sudoku[satir_nokta2.x, satir_nokta2.y] = satir_eksik1;
                                }
                            }
                        }
                        if (sutunda_bos_hucre_sayisi == 2)//////------Sutundaki bos hucre sayisi 2 ise-----/////
                        {
                            for (a = 1; a < 10; a++)/////-----Sutunu dolas ve eksik elemanlari bul-------/////
                            {
                                if (sutun_status[a] == true)/////-------Sutunda a degeri var ise----/////
                                {
                                    if (sutun_eksik1 == 0)/////------Birinci eksik elemani tutacak deger bos ise a degerini ona ata-----////
                                    {
                                        sutun_eksik1 = a;
                                    }
                                    else if(sutun_eksik2 == 0)/////------eger degilse digerine ata------/////
                                    {
                                        sutun_eksik2 = a;
                                    }
                                }
                            }
                            for (a = 0; a < 9; a++)/////-----Bos hucrenin bulundugu sutunlari dolas eger eksik elemanlardan herhangi biri bu sutunlarda bulunuyorsa eksik elemanlari uygun sekilde satira yerlestir-------/////
                            {
                                if (sudoku[a, sutun_nokta1.y] == sutun_eksik1)/////-----Bos hucrenin bulundugu satirlari dolas eger eksik elemanlardan herhangi biri bu satirlarda bulunuyorsa eksik elemanlari uygun sekilde sutuna yerlestir-------/////
                                {
                                    sudoku[sutun_nokta1.x, sutun_nokta1.y] = sutun_eksik2;
                                    sudoku[sutun_nokta2.x, sutun_nokta2.y] = sutun_eksik1;
                                }
                                if (sudoku[a, sutun_nokta1.y] == sutun_eksik2)
                                {
                                    sudoku[sutun_nokta1.x, sutun_nokta1.y] = sutun_eksik1;
                                    sudoku[sutun_nokta2.x, sutun_nokta2.y] = sutun_eksik2;
                                }
                                if (sudoku[a, sutun_nokta2.y] == sutun_eksik1)
                                {
                                    sudoku[sutun_nokta1.x, sutun_nokta1.y] = sutun_eksik1;
                                    sudoku[sutun_nokta2.x, sutun_nokta2.y] = sutun_eksik2;
                                }
                                if (sudoku[a, sutun_nokta2.y] == sutun_eksik2)
                                {
                                    sudoku[sutun_nokta1.x, sutun_nokta1.y] = sutun_eksik2;
                                    sudoku[sutun_nokta2.x, sutun_nokta2.y] = sutun_eksik1;
                                }
                            }
                        }
                    }
                }
            }
            return sudoku;
        }

        String stringeAl(int[,] sudoku)
        {
            int i, j;
            String sudo = "";
            for (i = 0; i < 9; i++)
            {
                //sudo += "\r\n|";
                for (j = 0; j < 9; j++)
                {
                    if (sudoku[i, j] != 0)
                    {
                        sudo += sudoku[i, j];
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

        void sudokularıGöster()
        {
            Form2 f2 = new Form2();
            f2.Show();
            Form3 f3 = new Form3();
            f3.Show();
            Form4 f4 = new Form4();
            f4.Show();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            sudokularıGöster();
        }
    }


    public class Nokta
    {
        public int x;
        public int y;
    }
}