
//Kütüphanelerin tanımlanması
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "driverlib/rom_map.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

void init_port_E() {//Port E'nin ayarlanması
	volatile unsigned long tmp; // bu degisken gecikme yapmak icin gerekli
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE; // 1) E portunun osilatörünü etkinleştir
	tmp = SYSCTL_RCGCGPIO_R;    	// zaman geçirmek için kullanılır
	GPIO_PORTE_LOCK_R = 0x4C4F434B;   // 2) portE yi açtım.
	GPIO_PORTE_CR_R = 0x3F; //PE5-0 değişikliklerine izin ver.Sadece PE0 kilidinin açılması gerekir, diğer bitler kilitlenemez
	GPIO_PORTE_AMSEL_R = 0x00;    	// 3) PE'de analog devre dışı bıraktım.
	GPIO_PORTE_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PE4-0
	GPIO_PORTE_DIR_R = 0x3F;      	// 5) PE4,PE5 in, PE3-0 out
	GPIO_PORTE_AFSEL_R = 0x00;    	// 6) disable alt funct on PE7-0
	GPIO_PORTE_PUR_R = 0x3F; //PE4 ve PE5'te pull up'ı etkinleştirdim (  Rs ve E için)

	GPIO_PORTE_DEN_R = 0x3F;      	// 7)portE 5-0 giriş çıkış  etkinlerştir.

	GPIO_PORTE_DATA_R |= 0b010000; // PE4 'ü çıkış yaptım.
	GPIO_PORTE_DATA_R |= 0b100000; // PE5’i çıkış yaptım.
}

void init_port_B() {//por B'nini ayarlanması
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB; // Port B nin aktifliğini sağlar
	delay = SYSCTL_RCGC2_R;  	// zaman geçirmek için kullanılır
	GPIO_PORTB_DIR_R |= 0xFF; // PB 7,6,5,4,3,2,1,0. pinlerin tamamını aktif eder.
	GPIO_PORTB_AFSEL_R &= ~0xFF; // PB 7,6,5,4,3,2,1,0 pinlerini alternatif fonksinunu 0 yapar.
	GPIO_PORTB_DEN_R |= 0xFF;	// PB 7,6,5,4,3,2,1,0 pinlerini aktiflestir
	GPIO_PORTB_DATA_R |= 0xf; // PB0, PB1, PB2 ve  PB3'ü çıkış yapar. LCD ile veri alışverişi yapacak pinler

}

//İnternetten alınan kısım 41 -180. Bazı değişiklikler yaparak kendi projeme uyarladım.
#define RS GPIO_PIN_4 // RS için Pin E4
#define EN GPIO_PIN_5 // E  için pin E5
#define D4 GPIO_PIN_0 // D4 için pin B0
#define D5 GPIO_PIN_1 // D5 için pin B1
#define D6 GPIO_PIN_2 // D6 için pin B2
#define D7 GPIO_PIN_3 // D7 için pin B3
#define ALLDATAPINS  D7 | D6 | D5 | D4
#define ALLCONTROLPINS RS | EN
#define FALSE false
#define TRUE true

#define DATA_PORT_BASE GPIO_PORTB_BASE
#define CMD_PORT_BASE GPIO_PORTE_BASE
#define DATA_PERIPH SYSCTL_PERIPH_GPIOD
#define CMD_PERIPH SYSCTL_PERIPH_GPIOE

void pulseLCD() {
	//Bu bir darbe pimi, LCD'nin veri yolundaki verileri kabul etmesi için Darbeli Düşük-Yüksek-Düşük olması gerekiyor.
	GPIOPinWrite(CMD_PORT_BASE, EN, 0);
	GPIOPinWrite(CMD_PORT_BASE, EN, EN);
	GPIOPinWrite(CMD_PORT_BASE, EN, 0);
}

//Veri yolunun yürütülecek bir komutu veya gösterilecek bir karakteri taşıdığını belirtir.
//RS düşük olduğunda,veriyolu üzerindeki veriler bir komutu temsil eder yüksek olduğunda ise bir karakteri temsil eder.
void setCmd() { //düşük
	GPIOPinWrite(CMD_PORT_BASE, RS, 0);
}

void setData() { //yüksek
	GPIOPinWrite(CMD_PORT_BASE, RS, RS);
}

void sendByte(char byteToSend, int isData) {
	if (isData)
		setData();
	else
		setCmd();
	SysCtlDelay(400);
	GPIOPinWrite(GPIO_PORTB_BASE, ALLDATAPINS, byteToSend >> 4);
	pulseLCD();
	GPIOPinWrite(GPIO_PORTB_BASE, ALLDATAPINS, byteToSend);
	pulseLCD();
}

void setCursorPositionLCD(char row, char col) // konum belirlemek için
{
	char address;
	//burada dört satırlık lcd için yapılan ayarlara tekrardan ayar çekilerek iki satırlık lcd için uyarlanmıştır
	if (row == 0)
		address = 0;
	else if (row == 1)
		address = 0x40;
	else
		address = 0;

	address |= col;

	sendByte(0x80 | address, FALSE);
}

// LCD'yi temizle
// ve ana pozisyona dön (0,0)
void clearLCD(void) {
	sendByte(0x01, FALSE);
	sendByte(0x02, FALSE);
	SysCtlDelay(30000);
}
// Başa dön konumuna dön (0,0)

void homeLCD(void) {
	sendByte(0x02, FALSE);
	SysCtlDelay(30000);
}

// Başa dön konumuna dön (0,0)
void setBlockCursorLCD(void) {
	sendByte(0x0F, FALSE);
}

// Satır imlecini görünür kıl

void setLineCursorLCD(void) {
	sendByte(0x0E, FALSE);
}

// Ekrana imleci göster
void cursorOnLCD(void) {
	sendByte(0x0E, FALSE);
}

// İmleci ekranda gizle

void cursorOffLCD(void) {
	sendByte(0x0C, FALSE);
}

// LCD'yi kapat

void displayOffLCD(void) {
	sendByte(0x08, FALSE);
}

//LCD yi aç
void displayOnLCD(void) {
	sendByte(0x0C, FALSE);
}

void initLCD(void) {

	SysCtlPeripheralEnable(DATA_PERIPH);
	SysCtlPeripheralEnable(CMD_PERIPH);
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, ALLDATAPINS);
	GPIOPinTypeGPIOOutput(CMD_PORT_BASE, ALLCONTROLPINS);
	GPIOPinWrite(GPIO_PORTB_BASE, ALLDATAPINS, 0);
	GPIOPinWrite(CMD_PORT_BASE, ALLCONTROLPINS, 0);

	SysCtlDelay(10000);

	setCmd();
	SysCtlDelay(15000);
	GPIOPinWrite(GPIO_PORTB_BASE, ALLDATAPINS, 0b0010);
	pulseLCD();
	GPIOPinWrite(GPIO_PORTB_BASE, ALLDATAPINS, 0b0010);
	pulseLCD();
	sendByte(0x28, FALSE); // İki satırı ayarla
	cursorOffLCD(); // İmleç görünmez
	sendByte(0x06, FALSE); //  Ekle modunu ayarla
	clearLCD();
}

void printLCD(char *text) {//alıntı kodda gereksiz yere tanımlanan değişken kaldırılarak .......

	while (*text != NULL) {///koşulda da ufak bir değişiklik yapılmıştır :))))
		SysCtlDelay(100);
		sendByte(*text, TRUE);
		text++;
	}
}

int main() {
	volatile unsigned long delay;

	//alıntı kodda kullanılan d portu koddan çıkarılıp daha derli toplu olmak adına b portunu diğer pinlerini de işbaşı yaptım
	init_port_B(); // port B  ayarları
	init_port_E(); // port E  ayarları

	int random; //rasgele led için
	int temp; //iki kez aynı sayıyı üretirse aynı ledi yakmamak için
	int row; //imlecin satır bilgisini tutar
	//döngüler içinde tanımlayacağım col değişkeni de sütun bilgisini tutmakta

	SysCtlClockSet(
	SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); //Sistem osilatör ayaralar1 40 Mhz e ayarlandi.

	/*Bu kod satırında 16 Mhz MAIN kristalin PLL ile birlikte kullanıldığı, SYSDIV tarafından 5 e bölünerek kullanılacağı belirtilmiştir.

	 Bu kod satırı ile 16 Mhz kristal PLL ile 400 MHz e çıkartılır,
	 önce diyagramdaki gibi 2 ye sonra da SYSDIV tarafından 5 e bölünür ve 400/5/2= 40 MHz e sistem clock u set edilmiş olur. /***

	 SysCtlDelay(1345000) saniyelik karşılıgı.
	 */

	initLCD();//lcd yi hazırla
	cursorOffLCD();//imleci lcd de sakla

	while (1) {

		//srand(time(NULL));
		random = rand()%4; //yukarıdaki satır hata verdiği için gerçek random değer üreten fonksiyonu kullanamadım :((( i am sorry.

		if(random == temp){//bir önceki random değerle aynı değer üretildiyse tekrardan bir random değer üret
			random = rand()%4;//0 ile 4 arasında random sayı üretip random değişkenin ata
		}


		if(random == 0){ //birinci durum
			GPIO_PORTB_DATA_R |= 0x10; //kırmzı ledi yak
			setCursorPositionLCD(0, 0); //imleci 0,0 noktasına al
			printLCD("Kocaeli Uni"); //lcd ye 'KOcaeli Uni' yazdır
			setCursorPositionLCD(1, 0);//mleci 1,0 nokasına al
			SysCtlDelay(26900000); //2 saniye bekle
			printLCD("Ilyas Mammadov "); //lcd ye  'ILyas Mammadov' yazdır
			SysCtlDelay(13450000); //bir saniye bekle
			clearLCD();//lcd yi temizle
			SysCtlDelay(40350000); //3 saniye bekle
			GPIO_PORTB_DATA_R &= ~0x10; //kırmızı ledi söndür
		}

		else if(random == 1) { //ikinci durum
			GPIO_PORTB_DATA_R |= 0x20; //Beyaz ledi yak
			setCursorPositionLCD(1, 0);//imleci 1,0 noktasına al
			printLCD("Ilyas Mammadov");//lcd ye 'Ilyas Mammadov' yazdır
			SysCtlDelay(26900000);//2 saniye bekle
			setCursorPositionLCD(0, 0);//imleci 0,0 noktasına al
			printLCD("Kocaeli Uni");//lcd ye 'KOcaeli Uni' yazdır
			SysCtlDelay(13450000);//bir saniye bekle
			clearLCD();//lcd ekranını temizle
			SysCtlDelay(40350000);//üç saniye bekle
			GPIO_PORTB_DATA_R &= ~0x20; //beyaz ledi sondür
		}

		else if(random == 2){ //üçüncü durum
			GPIO_PORTB_DATA_R |= 0x40; ///yeşil ledi yak

			row = 1; // satir değişkenini 1 yap
			for (int col = 28, i = 0; i <= 16; i++) { // kaydırma döngüsünü başlat
				(col + i == 41) ? i=1, col = 0, row = 0 : i; // imlecin aktif konumu birinci satırın sonuna eldiyse ikinci satırın başından devam etmek için gerekli ayarları yapar
				setCursorPositionLCD(row, col + i); //imlecin konumunu sürekli olarak güncellenen değerlere göre ayarlar
				printLCD("Kocaeli Uni"); //lcd'ye 'KOcaeli Uni' yazar
				SysCtlDelay(6000000); //kayma hızı
				clearLCD();//lcd ekranını temizler
			}
			SysCtlDelay(26900000); // iki saniye bekler
			for (int col = 26, j = 0; j <= 16; j++) {//kaydırma döngüsü
				(col + j == 40) ? j = 0, col = 0, row = 1 : j; // imlecin aktif konumu birinci satırın sonuna eldiyse ikinci satırın başından devam etmek için gerekli ayarları yapar
				setCursorPositionLCD(row, col + j);//imlecin konumunu sürekli olarak güncellenen değerlere göre ayarlar
				printLCD("Ilyas Mammadov");//lcd ye 'Ilyas Mammadov' yazdır
				SysCtlDelay(6000000); //kayma hızı
				clearLCD();//lcd ekranını temizler
			}

			SysCtlDelay(40350000); //üç saniye bekle
			GPIO_PORTB_DATA_R &= ~0x40; //yeşil ledi söndür
		}

		else if(random == 3) {//dördüncü durum
			GPIO_PORTB_DATA_R |= 0x80; //mavi ledi yak
			row = 0; // satır değişkenini ayarla
			for (int col = 0, m = 16; m >= 0; m--) {//kaydırma döngüsunu başlat
				(col + m == 0) ? row = 1, col = 28, m = 12 : m;// imlecin aktif konumu birinci satırın sonuna eldiyse ikinci satırın başından devam etmek için gerekli ayarları yapar
				setCursorPositionLCD(row,col + m);//imlecin konumunu sürekli olarak güncellenen değerlere göre ayarlar
				printLCD("Kocaeli Uni"); //lcd'ye 'KOcaeli Uni' yazar
				SysCtlDelay(6000000); //kayma hızı
				clearLCD(); //lcd ekranını temizler

			}
			SysCtlDelay(26900000);//iki saniye bekler
			row = 1;//satır ayarı
			for (int col = 0, f = 16; f >= 0; f--) {//ikinici kayma işlemi için döngü başlasın
				(col + f == 0) ? row = 0, col = 26, f =14 : f;// imlecin aktif konumu birinci satırın sonuna eldiyse ikinci satırın başından devam etmek için gerekli ayarları yapar
				setCursorPositionLCD(row, col + f);//imlecin konumunu sürekli olarak güncellenen değerlere göre ayarlar
				printLCD("Ilyas Mammadov");//lcd ye 'Ilyas Mammadov' yazdır
				SysCtlDelay(6000000);//kayma hızı
				clearLCD();//lcd ekranını temizler
			}

			SysCtlDelay(40350000); // üç saniye bekler
			GPIO_PORTB_DATA_R &= ~0x80;//mavi ledi söndürür
		}//dördüncü durum biter
		temp = random; //bir sonraki random değer ile karşılaştırmak için random değer geçici bir değişkene atanır.
	}//sonsuz döngü bitimi
}

