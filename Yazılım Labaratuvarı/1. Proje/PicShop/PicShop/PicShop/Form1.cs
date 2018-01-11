using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PicShop
{
    public partial class Form1 : Form
    {
        OpenFileDialog ofd = new OpenFileDialog();
        SaveFileDialog sfd = new SaveFileDialog();
        int[] gray_dengesi = new int[256];
        int[] red_dengesi = new int[256];
        int[] green_dengesi = new int[256];
        int[] blue_dengesi = new int[256];
        Bitmap orginal;
        Image ilkresim;
        bool resimYeni;
        bool bagli = true;

        public Form1()
        {
            InitializeComponent();
            pictureBox1.MouseWheel += PictureBox1_MouseWheel;
            pictureBox1.MouseHover += PictureBox1_MouseHover;
        }

        private void PictureBox1_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta != 0)
            {
                if (e.Delta > 0 && pictureBox1.Width < 5000)
                {
                    pictureBox1.Width += (pictureBox1.Width*5)/100;
                    pictureBox1.Height += (pictureBox1.Height * 5) / 100;
                }
                else if (e.Delta < 0 && pictureBox1.Width > 200)
                {
                    pictureBox1.Width -= (pictureBox1.Width * 5) / 100;
                    pictureBox1.Height -= (pictureBox1.Height * 5) / 100;
                }
                textBox1.Text = pictureBox1.Width.ToString();
                textBox2.Text = pictureBox1.Height.ToString();
            }
        }

        Image zoom(Image img, Size size)
        {
            Bitmap bmp = new Bitmap(img, img.Width + (img.Width * size.Width / 100), img.Height + (img.Height * size.Height / 100));
            Graphics g = Graphics.FromImage(bmp);
            g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
            return bmp;
        }

        private void PictureBox1_MouseHover(object sender, EventArgs e)
        {
            pictureBox1.Focus();
        }

        private void açToolStripMenuItem_Click(object sender, EventArgs e) //yeni dosya açma
        {
            using (OpenFileDialog ofd = new OpenFileDialog() { Multiselect = false, ValidateNames = true, Filter = "JPEG|*.*" })// open file dialog dahil ediliyor ve yeni nesne tanımlanıyor, gerekli ozellik değişimleri yapılıyor
            {
                if (ofd.ShowDialog() == DialogResult.OK)//dialog penceresi sorunsuz açıldı ise bu işlemleri yapar
                {
                    pictureBox1.Width = Image.FromFile(ofd.FileName).Width;
                    pictureBox1.Height = Image.FromFile(ofd.FileName).Height;
                    pictureBox1.Image = Image.FromFile(ofd.FileName);
                    ilkresim = pictureBox1.Image;
                }
                this.ofd.FileName = ofd.FileName;
                this.sfd.FileName = ofd.FileName;
                resimYeni = true;

                textBox1.Text = pictureBox1.Width.ToString();
                textBox2.Text = pictureBox1.Height.ToString();

                checkBox2.Checked = true;
                checkBox3.Checked = true;
                checkBox4.Checked = true;
            }

            if(pictureBox1.Width * pictureBox1.Height < 1000000)
                hisihesapla();
        }

        private void yenidenAçToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(pictureBox1.Image != null)
            {
                pictureBox1.ImageLocation = this.ofd.FileName;
                pictureBox1.Width =ilkresim.Width;
                pictureBox1.Height = ilkresim.Height;

                textBox1.Text = pictureBox1.Width.ToString();
                textBox2.Text = pictureBox1.Height.ToString();

                checkBox2.Checked = true;
                checkBox3.Checked = true;
                checkBox4.Checked = true;
            }
            else
            {
                MessageBox.Show("Bu işlem için bir resim açmış olmanız gerekir!", "Error!");
            }
        }

        private void kaydetToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Bu işlem şu anda aktif değil.", "Bilgi!");
        }

        private void farklıKaydetToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.Filter = "JPG|*.jpg|PNG|*.png|BITMAP|*.bmp";
            sfd.Title = "Kaydet";
            DialogResult sonuc = sfd.ShowDialog();

            if (sonuc == DialogResult.OK)
            {
                pictureBox1.Image.Save(sfd.FileName);
            }
        }

        private void çıkışToolStripMenuItem_Click(object sender, EventArgs e)
        {
            timer2.Enabled = true;
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                griyap();
            }
            else
            {
                MessageBox.Show("Bu işlem için bir resim açmış olmanız gerekir!", "Error!");
            }
        }

        private void griyap()
        {
            Bitmap image = new Bitmap(pictureBox1.Image);
            Color renk;
            int ortalama;
            for (int i = 0; i < image.Height; i++)
            {
                for (int j = 0; j < image.Width; j++)
                {
                    renk = image.GetPixel(j,i);
                    ortalama = (renk.R + renk.G + renk.B)/3;
                    renk = Color.FromArgb(ortalama, ortalama, ortalama);
                    image.SetPixel(j, i, renk);
                }
            }
            pictureBox1.Image = image;
        }

        private void toolStripButton2_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                negatif();
            }
            else
            {
                MessageBox.Show("Bu işlem için bir resim açmış olmanız gerekir!", "Error!");
            }
        }

        private void negatif()
        {
            Bitmap image = new Bitmap(pictureBox1.Image);
            Color renk;
            int red, green, blue;
            for (int i = 0; i < image.Height; i++)
            {
                for (int j = 0; j < image.Width; j++)
                {
                    renk = image.GetPixel(j,i);
                    red = 255 - renk.R;
                    green = 255 - renk.G;
                    blue = 255 - renk.B;

                    renk = Color.FromArgb(red, green, blue);
                    image.SetPixel(j, i, renk);
                }
            }
            pictureBox1.Image = image;
        }

        private void toolStripButton3_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                yatayaynala();
            }
            else
            {
                MessageBox.Show("Bu işlem için bir resim açmış olmanız gerekir!", "Error!");
            }
        }

        private void yatayaynala()
        {
            Bitmap image = new Bitmap(pictureBox1.Image);
            Color renk1, renk2;
            for (int i = 0; i < image.Height; i++)
            {
                for (int j = 0; j < image.Width / 2; j++)
                {
                    renk1 = image.GetPixel(j, i);
                    renk2 = image.GetPixel(image.Width - j - 1, i);
                    image.SetPixel(j, i, renk2);
                    image.SetPixel(image.Width - j - 1, i, renk1);
                }
            }
            pictureBox1.Image = image;
        }

        private void toolStripButton4_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                dikeyaynala();
            }
            else
            {
                MessageBox.Show("Bu işlem için bir resim açmış olmanız gerekir!", "Error!");
            }
        }

        private void dikeyaynala()
        {
            Bitmap image = new Bitmap(pictureBox1.Image);
            Color renk1, renk2;
            for (int i = 0; i < image.Height / 2; i++)
            {
                for (int j = 0; j < image.Width; j++)
                {
                    renk1 = image.GetPixel(j,i);
                    renk2 = image.GetPixel(j, image.Height - i - 1);
                    image.SetPixel(j, i, renk2);
                    image.SetPixel(j, image.Height - i - 1, renk1);
                }
            }
            pictureBox1.Image = image;
        }

        private void toolStripButton5_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                solaDondur();
            }
            else
            {
                MessageBox.Show("Bu işlem için bir resim açmış olmanız gerekir!", "Error!");
            }
        }

        private void solaDondur()
        {
            Bitmap temp = new Bitmap(pictureBox1.Image);
            Bitmap image = new Bitmap(temp, temp.Height, temp.Width);
            
            int i, j;
            Color renk;

            for (i = 1; i < temp.Height; i++)
            {
                for (j = temp.Width - 1; j > 0; j--)
                {
                    renk = temp.GetPixel(temp.Width - j, i);
                    image.SetPixel(i, j, renk);
                }
            }
            pictureBox1.Width = image.Width;
            pictureBox1.Height = image.Height;
            textBox1.Text = pictureBox1.Width.ToString();
            textBox2.Text = pictureBox1.Height.ToString();
            pictureBox1.Image = image;
        }

        private void toolStripButton6_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                sagaDondur();
            }
            else
            {
                MessageBox.Show("Bu işlem için bir resim açmış olmanız gerekir!", "Error!");
            }
        }

        private void sagaDondur()
        {
            Bitmap temp = new Bitmap(pictureBox1.Image);
            Bitmap image = new Bitmap(temp, temp.Height, temp.Width);
            
            int i, j;
            Color renk;

            for (i = 0; i < temp.Height; i++)
            {
                for (j = temp.Width - 1; j >= 0; j--)
                {
                    renk = temp.GetPixel(temp.Width - j - 1, i);
                    image.SetPixel(temp.Height - i - 1, image.Height - j - 1, renk);
                }
            }
            pictureBox1.Width = image.Width;
            pictureBox1.Height = image.Height;
            textBox1.Text = pictureBox1.Width.ToString();
            textBox2.Text = pictureBox1.Height.ToString();
            pictureBox1.Image = image;
        }

        private void toolStripButton7_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                hisihesapla();
            }
            else
            {
                MessageBox.Show("Bu işlem için bir resim açmış olmanız gerekir!", "Error!");
            }
        }

        private void hisihesapla()
        {
            int i, j;

            for (i = 0; i < 256; i++) //dizi elemanlarini sifirlar
            {
                this.red_dengesi[i] = 0;
                this.green_dengesi[i] = 0;
                this.blue_dengesi[i] = 0;
                this.gray_dengesi[i] = 0;
            }

            Bitmap bmp = new Bitmap(pictureBox1.Image);
            Color renk;

            for (i = 0; i < bmp.Height; i++)
            {
                for (j = 0; j < bmp.Width; j++)
                {
                    renk = bmp.GetPixel(j,i);

                    this.red_dengesi[renk.R]++;
                    this.green_dengesi[renk.G]++;
                    this.blue_dengesi[renk.B]++;
                    this.gray_dengesi[(renk.R+renk.G+renk.B)/3]++;
                }
            }
        }

        private void toolStripButton8_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                iyilestir();
            }
            else
            {
                MessageBox.Show("Bu işlem için bir resim açmış olmanız gerekir!", "Error!");
            }
        }

        private void iyilestir()
        {
            Bitmap image = new Bitmap(pictureBox1.Image);
            Color renk;

            int red, green, blue, redmax = 0, greenmax = 0, bluemax = 0, redmin = 255, greenmin = 255, bluemin = 255;

            for (int i = 0; i < image.Height; i++)
            {
                for (int j = 0; j < image.Width; j++)
                {
                    renk = image.GetPixel(j,i);

                    if (redmax < renk.R)
                        redmax = renk.R;
                    if (redmin > renk.R)
                        redmin = renk.R;
                    if (greenmax < renk.G)
                        greenmax = renk.G;
                    if (greenmin > renk.G)
                        greenmin = renk.G;
                    if (bluemax < renk.B)
                        bluemax = renk.B;
                    if (bluemin > renk.B)
                        bluemin = renk.B;
                }
            }

            int redfark = redmax - redmin;
            int greenfark = greenmax - greenmin;
            int bluefark = bluemax - bluemin;

            for (int i = 0; i < image.Height; i++)
            {
                for (int j = 0; j < image.Width; j++)
                {
                    renk = image.GetPixel(j, i);

                    red = (redfark == 0) ? 0 : ((renk.R - redmin) * 255) / redfark;
                    green = (greenfark == 0) ? 0 : ((renk.G - greenmin) * 255) / greenfark;
                    blue = (bluefark == 0) ? 0 : ((renk.B - bluemin) * 255) / bluefark;

                    renk = Color.FromArgb(red, green, blue);
                    image.SetPixel(j, i, renk);
                }
            }
            pictureBox1.Image = image;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            Color renk = Color.FromArgb(255, 255, 255);
            pictureBox2.Image = Image.FromFile("histogram.jpg");
            Bitmap image = new Bitmap(pictureBox2.Image);

            if (comboBox1.Text == "RGB")
            {
                int hisimax_gray = 0;

                if (pictureBox1.Image != null)
                {
                    for (int i = 0; i < 256; i++)
                    {
                        if (hisimax_gray < gray_dengesi[i])
                            hisimax_gray = gray_dengesi[i];
                    }

                    int hisi = 1;
                    if (hisimax_gray > 140)
                        hisi = (hisimax_gray / 140);

                    for (int j = 0; j < 256; j++)
                    {
                        for (int i = 145 - (gray_dengesi[j] / hisi); i < 140; i++)
                        {
                            image.SetPixel(j, i, renk);
                        }
                    }
                    pictureBox2.Image = image;
                }
                else
                {
                    MessageBox.Show("Bu işlem için bir resim açmış olmanız gerekir!", "Error!");
                }
            }
            else if (comboBox1.Text == "Kırmızı")
            {
                int hisimax_red = 0;

                if (pictureBox1.Image != null)
                {
                    for (int i = 0; i < 256; i++)
                    {
                        if (hisimax_red < red_dengesi[i])
                            hisimax_red = red_dengesi[i];
                    }

                    int hisi = 1;
                    if (hisimax_red > 140)
                        hisi = (hisimax_red / 140) + 1;

                    for (int j = 0; j < 256; j++)
                    {
                        for (int i = 145 - (red_dengesi[j] / hisi); i < 140; i++)
                        {
                            image.SetPixel(j, i, renk);
                        }
                    }
                    pictureBox2.Image = image;
                }
                else
                {
                    MessageBox.Show("Bu işlem için bir resim açmış olmanız gerekir!", "Error!");
                }
            }
            else if (comboBox1.Text == "Yeşil")
            {
                int hisimax_green = 0;

                if (pictureBox1.Image != null)
                {
                    for (int i = 0; i < 256; i++)
                    {
                        if (hisimax_green < green_dengesi[i])
                            hisimax_green = green_dengesi[i];
                    }

                    int hisi = 1;
                    if (hisimax_green > 140)
                        hisi = (hisimax_green / 140) + 1;

                    for (int j = 0; j < 256; j++)
                    {
                        for (int i = 145 - (green_dengesi[j] / hisi); i < 140; i++)
                        {
                            image.SetPixel(j, i, renk);
                        }
                    }
                    pictureBox2.Image = image;
                }
                else
                {
                    MessageBox.Show("Bu işlem için bir resim açmış olmanız gerekir!", "Error!");
                }
            }
            else if (comboBox1.Text == "Mavi")
            {
                int hisimax_blue = 0;

                if (pictureBox1.Image != null)
                {
                    for (int i = 0; i < 256; i++)
                    {
                        if (hisimax_blue < blue_dengesi[i])
                            hisimax_blue = blue_dengesi[i];
                    }

                    int hisi = 1;
                    if (hisimax_blue > 140)
                        hisi = (hisimax_blue / 140) + 1;

                    for (int j = 0; j < 256; j++)
                    {
                        for (int i = 145 - (blue_dengesi[j] / hisi); i < 140; i++)
                        {
                            image.SetPixel(j, i, renk);
                        }
                    }
                    pictureBox2.Image = image;
                }
                else
                {
                    MessageBox.Show("Bu işlem için bir resim açmış olmanız gerekir!", "Error!");
                }
            }
            else if (comboBox1.Text == "Renkler")
            {
                int hisimax_red = 0;
                int hisimax_green = 0;
                int hisimax_blue = 0;
                int hisimax;

                if (pictureBox1.Image != null)
                {
                    for (int i = 0; i < 256; i++)
                    {
                        if (hisimax_red < red_dengesi[i])
                            hisimax_red = red_dengesi[i];
                    }
                    for (int i = 0; i < 256; i++)
                    {
                        if (hisimax_green < green_dengesi[i])
                            hisimax_green = green_dengesi[i];
                    }
                    for (int i = 0; i < 256; i++)
                    {
                        if (hisimax_blue < blue_dengesi[i])
                            hisimax_blue = blue_dengesi[i];
                    }

                    if (hisimax_red > hisimax_green)
                    {
                        if (hisimax_red > hisimax_blue)
                            hisimax = hisimax_red;
                        else
                            hisimax = hisimax_blue;
                    }
                    else
                    {
                        if (hisimax_green > hisimax_blue)
                            hisimax = hisimax_green;
                        else
                            hisimax = hisimax_blue;
                    }

                    int hisi = 1;
                    if (hisimax > 140)
                        hisi = (hisimax / 140) + 1;

                    for (int j = 0; j < 256; j++)
                    {
                        Color renktemp;
                        for (int i = 145 - (red_dengesi[j] / hisi); i < 140; i++)
                        {
                            renktemp = image.GetPixel(j, i);
                            renk = Color.FromArgb(255, renktemp.G, renktemp.B);
                            image.SetPixel(j, i, renk);
                        }
                        for (int i = 145 - (green_dengesi[j] / hisi); i < 140; i++)
                        {
                            renktemp = image.GetPixel(j, i);
                            renk = Color.FromArgb(renktemp.R, 255, renktemp.B);
                            image.SetPixel(j, i, renk);
                        }
                        for (int i = 145 - (blue_dengesi[j] / hisi); i < 140; i++)
                        {
                            renktemp = image.GetPixel(j, i);
                            renk = Color.FromArgb(renktemp.R, renktemp.G, 255);
                            image.SetPixel(j, i, renk);
                        }
                    }
                    pictureBox2.Image = image;
                }
                else
                {
                    MessageBox.Show("Bu işlem için bir resim açmış olmanız gerekir!", "Error!");
                }
            }
        }

        private void vScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            pictureBox1.Top = -(pictureBox1.Height * vScrollBar1.Value) / vScrollBar1.Maximum;
        }

        private void hScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            pictureBox1.Left = -(pictureBox1.Width * hScrollBar1.Value) / hScrollBar1.Maximum;
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked == true)
            {
                checkBox1.Image = Image.FromFile("görünür.jpg");
                renkkanali();
                if ((checkBox2.Checked == false || checkBox3.Checked == false) || checkBox4.Checked == false)
                {
                    checkBox2.Checked = true;
                    checkBox3.Checked = true;
                    checkBox4.Checked = true;
                }
            }
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null && checkBox2.Checked == true)
            {
                checkBox2.Image = Image.FromFile("görünür.jpg");
                renkkanali();
            }
            else if (checkBox2.Checked == false)
            {
                checkBox2.Image = Image.FromFile("görünmez.jpg");
                checkBox1.Image = Image.FromFile("görünmez.jpg");
                checkBox1.Checked = false;
                renkkanali();
            }
            else
            {
                MessageBox.Show("Bu işlem için bir resim açmış olmanız gerekir!", "Error!");
            }
        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null && checkBox3.Checked == true)
            {
                checkBox3.Image = Image.FromFile("görünür.jpg");
                renkkanali();
            }
            else if (checkBox3.Checked == false)
            {
                checkBox3.Image = Image.FromFile("görünmez.jpg");
                checkBox1.Image = Image.FromFile("görünmez.jpg");
                checkBox1.Checked = false;
                renkkanali();
            }
            else
            {
                MessageBox.Show("Bu işlem için bir resim açmış olmanız gerekir!", "Error!");
            }
        }

        private void checkBox4_CheckedChanged(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null && checkBox4.Checked == true)
            {
                checkBox4.Image = Image.FromFile("görünür.jpg");
                renkkanali();
            }
            else if (checkBox4.Checked == false)
            {
                checkBox4.Image = Image.FromFile("görünmez.jpg");
                checkBox1.Image = Image.FromFile("görünmez.jpg");
                checkBox1.Checked = false;
                renkkanali();
            }
            else
            {
                MessageBox.Show("Bu işlem için bir resim açmış olmanız gerekir!", "Error!");
            }
        }

        private void renkkanali()
        {
            int red, green, blue, i, j;
            Bitmap image = new Bitmap(pictureBox1.Image);
            Color renktemp, renk = Color.FromArgb(0, 0, 0);

            if (orginal == null || this.resimYeni == true)
            {
                orginal = new Bitmap(pictureBox1.Image);
                this.resimYeni = false;
            }

            if ((checkBox2.Checked == true && checkBox3.Checked == true) && checkBox4.Checked == true)
            {
                image = orginal;
                checkBox1.Checked = true;
            }
            else if (checkBox2.Checked == true && checkBox3.Checked == true)
            {
                for (i = 0; i < orginal.Height; i++)
                {
                    for (j = 0; j < orginal.Width; j++)
                    {
                        renktemp = orginal.GetPixel(j, i);
                        renk = Color.FromArgb(renktemp.R, renktemp.G, 0);
                        image.SetPixel(j, i, renk);
                    }
                }
            }
            else if (checkBox3.Checked == true && checkBox4.Checked == true)
            {
                for (i = 0; i < orginal.Height; i++)
                {
                    for (j = 0; j < orginal.Width; j++)
                    {
                        renktemp = orginal.GetPixel(j, i);
                        renk = Color.FromArgb(0, renktemp.G, renktemp.B);
                        image.SetPixel(j, i, renk);
                    }
                }
            }
            else if (checkBox2.Checked == true && checkBox4.Checked == true)
            {
                for (i = 0; i < orginal.Height; i++)
                {
                    for (j = 0; j < orginal.Width; j++)
                    {
                        renktemp = orginal.GetPixel(j, i);
                        renk = Color.FromArgb(renktemp.R, 0, renktemp.B);
                        image.SetPixel(j, i, renk);
                    }
                }
            }
            else if (checkBox2.Checked == true)
            {
                for (i = 0; i < orginal.Height; i++)
                {
                    for (j = 0; j < orginal.Width; j++)
                    {
                        red = orginal.GetPixel(j, i).R;
                        renk = Color.FromArgb(red, 0, 0);
                        image.SetPixel(j, i, renk);
                    }
                }
            }
            else if (checkBox3.Checked == true)
            {
                for (i = 0; i < orginal.Height; i++)
                {
                    for (j = 0; j < orginal.Width; j++)
                    {
                        green = orginal.GetPixel(j, i).G;
                        renk = Color.FromArgb(0, green, 0);
                        image.SetPixel(j, i, renk);
                    }
                }
            }
            else if (checkBox4.Checked == true)
            {
                for (i = 0; i < orginal.Height; i++)
                {
                    for (j = 0; j < orginal.Width; j++)
                    {
                        blue = orginal.GetPixel(j, i).B;
                        renk = Color.FromArgb(0, 0, blue);
                        image.SetPixel(j, i, renk);
                    }
                }
            }
            else if ((checkBox2.Checked == false && checkBox3.Checked == false) && checkBox4.Checked == false)
            {
                for (i = 0; i < orginal.Height; i++)
                {
                    for (j = 0; j < orginal.Width; j++)
                    {
                        image.SetPixel(j, i, renk);
                    }
                }
            }
            pictureBox1.Image = image;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (bagli == true)
            {
                bagli = false;
                button1.BackgroundImage = Image.FromFile("açık kilit.png");
            }
            else
            {
                bagli = true;
                button1.BackgroundImage = Image.FromFile("kapalı kilit.png");
            }
        }

        private void textBox2_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                if (bagli == true)
                {
                    pictureBox1.Width = pictureBox1.Width * Convert.ToInt32(textBox2.Text) / pictureBox1.Height;
                    pictureBox1.Height = Convert.ToInt32(textBox2.Text);
                }
                else
                {
                    pictureBox1.Height = Convert.ToInt32(textBox2.Text);
                }
                textBox1.Text = pictureBox1.Width.ToString();
            }
        }

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                if (bagli == true)
                {
                    pictureBox1.Height = pictureBox1.Height * Convert.ToInt32(textBox1.Text) / pictureBox1.Width;
                    pictureBox1.Width = Convert.ToInt32(textBox1.Text);
                }
                else
                {
                    pictureBox1.Width = Convert.ToInt32(textBox1.Text);
                }
                textBox2.Text = pictureBox1.Height.ToString();
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if(this.Opacity < 0.8)
            {
                this.Opacity += 0.05;
            }
            else
            {
                timer1.Enabled = false;
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            timer1.Enabled = true;
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            if(this.Opacity > 0.0)
            {
                this.Opacity -= 0.05;
            }
            else
            {
                timer2.Enabled = false;
                this.Close();
            }
        }
    }
}
