/****************************************************************************
** 						SAKARYA UNIVERSITESI
** 					   FEN EDEBIYAT FAKULTESI
** 					      MATEMATIK BOLUMU
**					 PROGRAMLAMAYA GIRIS DERSI
**
** 				ODEV NUMARASI....: PROJE
** 				OGRENCI ADI......: Mustafa USTA
** 				OGRENCI NUMARASI.: B180200371
** 				DERS GRUBU.......: A
****************************************************************************/
#include <iostream>		// cin, cout gibi std komutlarinin kullanimi icin gerekli
#include <fstream>		// dosyalama islemleri icin gerekli
#include <windows.h>	// Sleep gibi system komutlarý icin gerekli
#include <iomanip>		// setw, setprecision gibi fonk.lar icin gerekli
#include <conio.h>		// getch() fonk.u icin gerekli

using namespace std;

// fonksiyon prototipleri
void secenekleriYazdir();		// kullanici arayuzundeki secenekler
void ogrenciKaydi();			// yeni ogrenci kaydi
void ogrenciKaydiGuncelleme();	// var olan ogrenci guncelleme
void ogrenciKaydiSilme();		// var olan ogrenci silme
void personelKaydi();			// yeni personel kaydi
void personelKaydiGuncelleme();	// var olan personel guncelleme
void personelKaydiSilme();		// var olan personel silme
void ogrenciSorgula();			// tc bilgisi ile ogrenci sorgulama
void ogrenciListesi();			// tum ogrencileri listele
void personelListesi();			// tum personelleri listele
bool tcSorgu(string sorgulanacakTc);	// tc no kisiye ozeldir. daha onceden kayit var mi bak

// global degisken veya nesne tanimlari
fstream dosya;			// temel dosya islemleri icin nesne olusturuldu
bool sorgu = false;		// ortak
string tcNo, ad, soyad, dogTarihi, bolum, test;		// ortak
string kayitTarihi, aldigiDersler;					// ogrenci
string iseBaslamaTarihi, unvan, verdigiDersler;		// personel
unsigned int ogrNo;		// ogrenci
unsigned int sicilNo;	// personel

// ana fonksiyon
int main() {
	// degisken tanimlamalari
	short secim;			// yapilacak islemin secilmesi
		
	// kullanici cikmak isteyene kadar programin calismasini surduren dongu
	do {
		secenekleriYazdir();
		cin >> secim;
		switch (secim) {
			// Ogrenci kaydi
			case 1: ogrenciKaydi(); break;
			// Ogrenci kaydi guncelleme
			case 2: ogrenciKaydiGuncelleme(); break;
			// Ogrenci silme (tum bilgiler silinecek)
			case 3: ogrenciKaydiSilme(); break;
			// Personel kaydi
			case 4: personelKaydi(); break;
			// Personel kaydi guncelleme
			case 5: personelKaydiGuncelleme(); break;
			// Personel silme (tum bilgiler silinecek)
			case 6: personelKaydiSilme(); break;
			// Ogrenci sorgulama
			case 7: ogrenciSorgula(); break;
			// Kayitli ogrenci listesi cikarma
			case 8: ogrenciListesi(); break;
			// Personel listesi cikarma
			case 9: personelListesi(); break;
			// Programi sonlandir
			case 0: continue;
			// Seceneklerin disinda yapilan secim
			default:
				cout << "Gecersiz giris yapildi. Tekrar giris icin yonlendiriliyor..." << endl;
				Sleep(2000);
				break;
		}
		system("CLS");		// konsol ekranini temizler
		dosya.close();		// dosya islemleri icin olusturulan genel amacli nesneyi dosya acmis olma ihtimaline karsi kapama
	} while (secim != 0);	// secim 0 olmadigi surece dongude kal	
	return 0;
}

//	Ekrana kullanicinin secebilecegi alternatifleri yazdirir
void secenekleriYazdir() {
	cout << "1 - Ogrenci kaydi\n"
		 << "2 - Ogrenci kaydi guncelleme\n"
		 << "3 - Ogrenci silme (tum bilgiler silinecek)\n"
		 << "4 - Personel kaydi\n"
		 << "5 - Personel kaydi guncelleme\n"
		 << "6 - Personel silme (tum bilgiler silinecek)\n"
		 << "7 - Ogrenci sorgulama\n"
		 << "8 - Kayitli ogrenci listesi cikarma\n"
		 << "9 - Personel listesi cikarma\n"
		 << "0 - Programi sonlandir\n"
		 << "\nLutfen seciniz: ";
	return;
}

//	Ogrenci kaydini gerceklestiren fonksiyon
void ogrenciKaydi() {
	dosya.open("ogrenci.txt", ios::app | ios::in);	// hem okuma hem yazma modunda dosya acildi
	system("CLS");
	cout << "YENI OGRENCI KAYIT GIRISI\n" << endl;
	if (dosya.is_open()) {	// dosyanin acilip acilmadigini garantilemek icin kontrol ederek islem yapildi
		if (!dosya.eof()) dosya << endl;	// dosya bos degilse alt satir girisi yap
		cout << "Ogrenci TC no giriniz: ";
		cin >> tcNo;
		cout << "Ogrenci adini giriniz: ";
		cin >> ad;
		cout << "Ogrenci soyadini giriniz: ";
		cin >> soyad;
		cout << "Ogrenci no giriniz: ";
		cin >> ogrNo;
		cout << "Ogrenci dogum tarihini giriniz (GUN.AY.YIL): ";
		cin >> dogTarihi;
		cout << "Ogrenci bolum giriniz: ";
		cin >> bolum;
		cout << "Ogrenci kayit tarihini giriniz (YIL): ";
		cin >> kayitTarihi;
		cout << "Ogrencinin aldigi dersleri giriniz (birden fazla ders icin"
			 << " aralara ',' koyunuz ve hic bosluk kullanmayiniz): ";
		cin >> aldigiDersler;
	}
	if (!tcSorgu(tcNo)) {	// daha once ayni tc no ile kayit olan biri var mi seklindeki kontrol blogu
		cout << "\nBu TC ye sahip bir kayit bulunmaktadir." << endl;
		Sleep(2000);	// programi 2 sn beklet (2000 milisaniye)
		return;
	}
	else	// daha once bu tc no ile kayitli birisi yoksa alinan dosyaya yazilabilir
		dosya << tcNo << ' ' << ad << ' ' << soyad << ' ' << ogrNo << ' '
			  << dogTarihi << ' ' << bolum << ' ' << kayitTarihi << ' ' << aldigiDersler;
	cout << "Kayit basarili." << endl;
	Sleep(2000);
	dosya.close();
	return;
}

//	istenilen ogrenciyi guncelleme
void ogrenciKaydiGuncelleme() {
	sorgu = false;
	string sorguTcNo;
	short kayitSayisi = 0;
	system("CLS");
	dosya.open("ogrenci.txt", ios::app | ios::in | ios::out);
	dosya >> test;	// dosyanin basina endl ekledigimiz icin onu gecmek ugruna yazilan kod
	if (dosya.eof()) {	// endl okutulduktan sonra kayit yoksa bu fonk. 1 degerini dondurur ve bloga girer
		cout << "Kayit yok." << endl;
	}
	else {	// kayit varsa ogrenci kaydi guncellemesi islemleri yapilabilir
		dosya.close();	// imleci en basa sarmak icin dosya kapatildi ve hemen ardindan tekrar acildi
		dosya.open("ogrenci.txt", ios::app | ios::in | ios::out);
		ofstream dosyaYaz("gecici.tmp");	// dosyamizi yapilacak islem sonunda yedekleyecegimiz out file nesnesi
		cout << "Guncellemek istediginiz ogrencinin tc no giriniz: ";
		cin >> sorguTcNo;
		while (!dosya.eof()) { // dosya sonuna kadar oku
			kayitSayisi++;
			dosya >> tcNo >> ad >> soyad >> ogrNo >> dogTarihi >> bolum >> kayitTarihi >> aldigiDersler;
			if (sorguTcNo == tcNo) { // ogrenci bulundu
				cout << "\n\t\tOGRENCI BILGILERI" << endl;
				cout << "AD: " << ad
					 << "\nSOYAD: " << soyad
					 << "\nOGRENCI NO: " << ogrNo
					 << "\nDOGUM TARIHI: " << dogTarihi
					 << "\nBOLUM: " << bolum
					 << "\nKAYIT TARIHI: " << kayitTarihi
					 << "\nALDIGI DERSLER: " << aldigiDersler << endl;
				cout << "\nOGRENCI BILGILERINI GUNCELLEYINIZ...\n"	// VERI GIRISI
					 << "ad giriniz: "; cin >> ad;
				cout << "soyad giriniz: "; cin >> soyad;
				cout << "ogrenci no giriniz: "; cin >> ogrNo;
				cout << "dogum tarihi giriniz: "; cin >> dogTarihi;
				cout << "bolum giriniz: "; cin >> bolum;
				cout << "kayit tarihi giriniz: "; cin >> kayitTarihi;
				cout << "Ogrencinin aldigi dersleri giriniz (birden fazla ders icin"
					 << " aralara ',' koyunuz ve hic bosluk kullanmayiniz): ";
				cin >> aldigiDersler;
				if (!dosyaYaz.eof()) dosyaYaz << endl;	// dosya sonuna gelinmediyse endl ekle
				dosyaYaz << tcNo << ' ' << ad << ' ' << soyad << ' ' << ogrNo << ' ' << dogTarihi << ' '
						 << bolum << ' ' << kayitTarihi << ' ' << aldigiDersler;
				sorgu = true;	// sorguTcNo ile tcNo eslesti. kayit var
			}
			else { // diger bilgileri yazdir
				if (dosya.eof()) {	// dosya sonuna gelindi ise (ogrenci.txt)
					if (!dosyaYaz.eof() && kayitSayisi != 1) dosyaYaz << endl;	// dosyaYaz sonuna gelinmedi ise endl ekle
					dosyaYaz << tcNo << ' ' << ad << ' ' << soyad << ' ' << ogrNo << ' ' << dogTarihi << ' '
							 << bolum << ' ' << kayitTarihi << ' ' << aldigiDersler;
					if (kayitSayisi != 1)	// yalniz bir kayit varsa dosyayi erken kapama
						dosyaYaz.close();	// dosyaYaz nesnesinin actigi dosyayi (gecici.tmp) kapat
				}
				else {	// dosya sonuna (ogrenci.txt) gelinmediyse
					if (!dosyaYaz.eof()) dosyaYaz << endl;
					dosyaYaz << tcNo << ' ' << ad << ' ' << soyad << ' ' << ogrNo << ' ' << dogTarihi << ' '
							 << bolum << ' ' << kayitTarihi << ' ' << aldigiDersler;
				}	
			}
		}
		dosyaYaz.close();
		if (!sorgu)	cout << "Kayit bulunamadi." << endl;	// sorgu false olursa if calisir (tc eslesemedi)
		dosya.close();
		remove("ogrenci.txt");	// eski ogrenci.txt dosyasi kaldirildi
		rename("gecici.tmp", "ogrenci.txt");	// yeni gecici dosyasinin adini ogrenci.txt yap
	}
	cout << "Islem tamamlandi, ana menuye yonlendiriliyorsunuz..." << endl;
	Sleep(2000);	// 2 sn beklet programi
	return;
}

//	ogrenci kayit silme
void ogrenciKaydiSilme() {
	sorgu = false;
	string sorguTcNo;
	short kayitSayisi = 0;
	char onay;	// kayit silmeye emin misiniz sorusunun yanitini tutan degisken
	system("CLS");
	dosya.open("ogrenci.txt", ios::app | ios::in | ios::out);
	dosya >> test;
	if (dosya.eof()) {	// yukaridaki yapinin aynisi. kayit yoksa islem yapilamaz
		cout << "Kayit yok." << endl;
	}
	else {
		dosya.close();
		dosya.open("ogrenci.txt", ios::app | ios::in | ios::out);
		ofstream dosyaYaz("gecici.tmp");
		cout << "Kaydini silmek istediginiz ogrencinin tc no giriniz: ";
		cin >> sorguTcNo;
		while (!dosya.eof()) { // dosya sonuna kadar oku
			kayitSayisi++;
			dosya >> tcNo >> ad >> soyad >> ogrNo >> dogTarihi >> bolum >> kayitTarihi >> aldigiDersler;
			if (sorguTcNo == tcNo) { // ogrenci bulundu
				cout << "\n\t\tOGRENCI BILGILERI" << endl;
				cout << "AD: " << ad
					 << "\nSOYAD: " << soyad
					 << "\nOGRENCI NO: " << ogrNo
					 << "\nDOGUM TARIHI: " << dogTarihi
					 << "\nBOLUM: " << bolum
					 << "\nKAYIT TARIHI: " << kayitTarihi
					 << "\nALDIGI DERSLER: " << aldigiDersler << endl;
				do {	// dogru karakter girisi yapilana kadar dongude kal
					cout << "\n\nSilmek istediginize emin misiniz(e/h): ";
					cin >> onay;
					if (onay == 'e' || onay == 'E') break;	// kaydi sil
					else if (onay == 'h' || onay == 'H') {	// kaydi tut
						if (!dosyaYaz.eof()) dosyaYaz << endl;
						dosyaYaz << tcNo << ' ' << ad << ' ' << soyad << ' ' << ogrNo << ' ' << dogTarihi << ' '
								 << bolum << ' ' << kayitTarihi << ' ' << aldigiDersler;
						break;
					}
					else cout << "\nYanlis karakter girisi! Silme gerceklesemedi. Tekrar giris yapin: ";
				} while (true);
				sorgu = true;
			}
			else { // diger bilgileri yazdir
				if (dosya.eof()) {
					if (!dosyaYaz.eof() && kayitSayisi != 1) dosyaYaz << endl;
					dosyaYaz << tcNo << ' ' << ad << ' ' << soyad << ' ' << ogrNo << ' ' << dogTarihi << ' '
							 << bolum << ' ' << kayitTarihi << ' ' << aldigiDersler;
					if (kayitSayisi != 1) dosyaYaz.close();
				}
				else {
					if (!dosyaYaz.eof()) dosyaYaz << endl;
					dosyaYaz << tcNo << ' ' << ad << ' ' << soyad << ' ' << ogrNo << ' ' << dogTarihi << ' '
							 << bolum << ' ' << kayitTarihi << ' ' << aldigiDersler;
				}
			}
		}
		dosyaYaz.close();
		if (!sorgu)	cout << "Kayit bulunamadi." << endl;
		dosya.close();
		remove("ogrenci.txt");
		rename("gecici.tmp", "ogrenci.txt");
	}
	cout << "Islem tamamlandi, ana menuye yonlendiriliyorsunuz..." << endl;
	Sleep(2000);
	return;
}

//	Personel kaydini gerceklestiren fonksiyon
void personelKaydi() {
	dosya.open("personel.txt", ios::app | ios::in);
	system("CLS");
	cout << "YENI PERSONEL KAYIT GIRISI\n" << endl;
	if (dosya.is_open()) {
		if (!dosya.eof()) dosya << endl;
		cout << "Personel TC no giriniz: ";
		cin >> tcNo;
		cout << "Personel adini giriniz: ";
		cin >> ad;
		cout << "Personel soyadini giriniz: ";
		cin >> soyad;
		cout << "Personel unvanini giriniz: ";
		cin >> unvan;
		cout << "Personel sicil no giriniz: ";
		cin >> sicilNo;
		cout << "Personel dogum tarihini giriniz (GUN.AY.YIL): ";
		cin >> dogTarihi;
		cout << "Personel bolum giriniz: ";
		cin >> bolum;
		cout << "Personel ise baslama tarihini giriniz (YIL): ";
		cin >> iseBaslamaTarihi;
		cout << "Personelin verdigi dersleri giriniz (birden fazla ders icin"
			 << " aralara ',' koyunuz ve hic bosluk kullanmayiniz): ";
		cin >> verdigiDersler;
	}
	if (!tcSorgu(tcNo)) {
		cout << "\nBu TC ye sahip bir kayit bulunmaktadir." << endl;
		Sleep(2000);
		return;
	}
	else
		dosya << tcNo << ' ' << ad << ' ' << soyad << ' ' << unvan << ' ' << sicilNo << ' '
			  << dogTarihi << ' ' << bolum << ' ' << iseBaslamaTarihi << ' ' << verdigiDersler;
	dosya.close();
	cout << "Kayit basarili." << endl;
	Sleep(2000);
	return;
}

//	istenilen personeli guncelleme
void personelKaydiGuncelleme() {
	string sorguTcNo;
	short kayitSayisi = 0;
	bool sorgu = false;
	system("CLS");
	dosya.open("personel.txt", ios::app | ios::in | ios::out);
	dosya >> test;
	if (dosya.eof()) {
		cout << "Kayit yok." << endl;
	}
	else {
		dosya.close();
		dosya.open("personel.txt", ios::app | ios::in | ios::out);
		ofstream dosyaYaz("gecici.tmp");
		cout << "Guncellemek istediginiz personelin tc no giriniz: ";
		cin >> sorguTcNo;
		dosya.close();
		dosya.open("personel.txt", ios::app | ios::in | ios::out);
		while (!dosya.eof()) { // dosya sonuna kadar oku
			kayitSayisi++;
			dosya >> tcNo >> ad >> soyad >> unvan >> sicilNo >> dogTarihi >> bolum
				  >> iseBaslamaTarihi >> verdigiDersler;
			if (sorguTcNo == tcNo) { // personel bulundu
				cout << "\n\t\tPERSONEL BILGILERI" << endl;
				cout << "AD: " << ad
					 << "\nSOYAD: " << soyad
					 << "\nUNVAN: " << unvan
					 << "\nSICIL NO: " << sicilNo
					 << "\nDOGUM TARIHI: " << dogTarihi
					 << "\nBOLUM: " << bolum
					 << "\nISE BASLAMA TARIHI: " << iseBaslamaTarihi
					 << "\nVERDIGI DERSLER: " << verdigiDersler << endl;
				cout << "\nPERSONEL BILGILERINI GUNCELLEYINIZ...\n"	// VERI GIRISI
					 << "ad giriniz: "; cin >> ad;
				cout << "soyad giriniz: "; cin >> soyad;
				cout << "unvan giriniz: "; cin >> unvan;
				cout << "personel no giriniz: "; cin >> sicilNo;
				cout << "dogum tarihi giriniz: "; cin >> dogTarihi;
				cout << "bolum giriniz: "; cin >> bolum;
				cout << "kayit tarihi giriniz: "; cin >> kayitTarihi;
				cout << "Personelin verdigi dersleri giriniz (birden fazla ders icin"
					 << " aralara ',' koyunuz ve hic bosluk kullanmayiniz): ";
				cin >> verdigiDersler;
				if (!dosyaYaz.eof() && kayitSayisi != 1) dosyaYaz << endl;
				dosyaYaz << tcNo << ' ' << ad << ' ' << soyad << ' ' << unvan << ' ' << sicilNo << ' ' << dogTarihi << ' '
						 << bolum << ' ' << iseBaslamaTarihi << ' ' << verdigiDersler;
				if (kayitSayisi != 1)	// yalniz bir kayit varsa dosyayi erken kapama
						dosyaYaz.close();	// dosyaYaz nesnesinin actigi dosyayi (gecici.tmp) kapat
				sorgu = true;
			}
			else { // diger bilgileri yazdir
				if (dosya.eof()) {
					if (!dosyaYaz.eof()) dosyaYaz << endl;
					dosyaYaz << tcNo << ' ' << ad << ' ' << soyad << ' ' << unvan << ' ' << sicilNo << ' ' << dogTarihi << ' '
							 << bolum << ' ' << iseBaslamaTarihi << ' ' << verdigiDersler;
					dosyaYaz.close();
				}
				else {
					if (!dosyaYaz.eof()) dosyaYaz << endl;
					dosyaYaz << tcNo << ' ' << ad << ' ' << soyad << ' ' << unvan << ' ' << sicilNo << ' ' << dogTarihi << ' '
							 << bolum << ' ' << iseBaslamaTarihi << ' ' << verdigiDersler;
				}
			}
		}
		dosyaYaz.close();
		if (!sorgu)	cout << "Kayit bulunamadi." << endl;
		dosya.close();
		remove("personel.txt");
		rename("gecici.tmp", "personel.txt");
	}
	cout << "Islem tamamlandi, ana menuye yonlendiriliyorsunuz..." << endl;
	Sleep(2000);
	return;
}

//	personel kayit silme
void personelKaydiSilme() {
	string sorguTcNo;
	short kayitSayisi = 0;
	char onay;
	dosya.open("personel.txt", ios::app | ios::in | ios::out);
	dosya >> test;
	system("CLS");
	if (dosya.eof()) {
		cout << "Kayit yok." << endl;
	}
	else {
		dosya.close();
		dosya.open("personel.txt", ios::app | ios::in | ios::out);
		ofstream dosyaYaz("gecici.tmp");
		cout << "Kaydini silmek istediginiz personelin tc no giriniz: ";
		cin >> sorguTcNo;
		while (!dosya.eof()) { // dosya sonuna kadar oku
			kayitSayisi++;
			dosya >> tcNo >> ad >> soyad >> unvan >> sicilNo >> dogTarihi
				  >> bolum >> iseBaslamaTarihi >> verdigiDersler;
			if (sorguTcNo == tcNo) { // personel bulundu
				cout << "\n\t\tPERSONEL BILGILERI" << endl;
				cout << "AD: " << ad
					 << "\nSOYAD: " << soyad
					 << "\nUNVAN: " << unvan
					 << "\nSICIL NO: " << sicilNo
					 << "\nDOGUM TARIHI: " << dogTarihi
					 << "\nBOLUM: " << bolum
					 << "\nISE BASLAMA TARIHI: " << iseBaslamaTarihi
					 << "\nVERDIGI DERSLER: " << verdigiDersler << endl;
				do {
					cout << "\n\nSilmek istediginize emin misiniz(e/h): ";
					cin >> onay;
					if (onay == 'e' || onay == 'E') break;
					else {
						if (!dosyaYaz.eof()) dosyaYaz << endl;
						dosyaYaz << tcNo << ' ' << ad << ' ' << soyad << ' ' << unvan << ' ' << sicilNo << ' ' << dogTarihi
								 << ' ' << bolum << ' ' << iseBaslamaTarihi << ' ' << verdigiDersler;
						break;
					}
				} while (true);
				sorgu = true;
			}
			else { // diger bilgileri yazdir
				if (dosya.eof()) {
					if (!dosyaYaz.eof() && kayitSayisi != 1) dosyaYaz << endl;
					dosyaYaz << tcNo << ' ' << ad << ' ' << soyad << ' ' << unvan << ' ' << sicilNo << ' ' << dogTarihi << ' '
							 << bolum << ' ' << iseBaslamaTarihi << ' ' << verdigiDersler;
					if (kayitSayisi != 1) dosyaYaz.close();
				}
				else {
					if (!dosyaYaz.eof()) dosyaYaz << endl;
					dosyaYaz << tcNo << ' ' << ad << ' ' << soyad << ' ' << unvan << ' ' << sicilNo << ' ' << dogTarihi << ' '
							 << bolum << ' ' << iseBaslamaTarihi << ' ' << verdigiDersler;
				}
			}
		}
		dosyaYaz.close();
		if (!sorgu)	cout << "Kayit bulunamadi." << endl;
		dosya.close();
		remove("personel.txt");
		rename("gecici.tmp", "personel.txt");
	}
	cout << "Islem tamamlandi, ana menuye yonlendiriliyorsunuz..." << endl;
	Sleep(2000);
	return;
}

//	ogrenci sorgula ve bilgileri getir
void ogrenciSorgula() {
	string sorguTcNo;
	sorgu = false;
	system("CLS");
	dosya.open("ogrenci.txt", ios::app | ios::in | ios::out);
	dosya >> test;
	if (dosya.eof()) {
		cout << "Kayit yok." << endl;
	}
	else {
		dosya.close();
		dosya.open("ogrenci.txt", ios::app | ios::in | ios::out);
		cout << "Sorgulamak istediginiz ogrencinin tc no giriniz: ";
		cin >> sorguTcNo;
		while (!dosya.eof()) { // dosya sonuna kadar oku
			dosya >> tcNo >> ad >> soyad >> ogrNo >> dogTarihi >> bolum >> kayitTarihi >> aldigiDersler;
			if (sorguTcNo == tcNo) { // ogrenci bulundu
				cout << "\n\t\tOGRENCI BILGILERI" << endl;
				cout << "\nAD: " << ad
					 << "\nSOYAD: " << soyad
					 << "\nOGRENCI NO: " << ogrNo
					 << "\nDOGUM TARIHI: " << dogTarihi
					 << "\nBOLUM: " << bolum
					 << "\nKAYIT TARIHI: " << kayitTarihi
					 << "\nALDIGI DERSLER: " << aldigiDersler << endl;
				sorgu = true;
			}
		}
		if (!sorgu)	cout << "Kayit bulunamadi." << endl;
	}
	dosya.close();
	cout << "\n\nAna menuye donmek icin bir tusa basin..." << endl;
	getch();
	return;
}

//	kayitli ogrencilerin listesini yazdirir
void ogrenciListesi() {
	dosya.open("ogrenci.txt", ios::app | ios::in | ios::out);
	dosya >> test;
	system("CLS");
	if (dosya.eof()) {
		cout << "Kayit yok." << endl;
	}
	else {
		dosya.close();
		dosya.open("ogrenci.txt", ios::app | ios::in | ios::out);
		cout << setw(60) << "OGRENCI LISTESI" << endl
			 << setw(11) << "TC NO"
			 << setw(10) << "AD"
			 << setw(10) << "SOYAD"
			 << setw(15) << "OGRENCI NO"
			 << setw(15) << "DOG TARIHI"
			 << setw(15) << "BOLUM"
			 << setw(15) << "KAYIT YIL"
			 << setw(25) << "ALDIGI DERSLER" << endl;
		while (!dosya.eof()) {
			dosya >> tcNo >> ad >> soyad >> ogrNo >> dogTarihi >> bolum >> kayitTarihi >> aldigiDersler;
			cout << setw(11) << tcNo
				 << setw(10) << ad
				 << setw(10) << soyad
				 << setw(15) << ogrNo
				 << setw(15) << dogTarihi
				 << setw(15) << bolum
				 << setw(15) << kayitTarihi
				 << setw(25) << aldigiDersler << endl;
		}
	}
	dosya.close();
	cout << "\n\nAna menuye donmek icin bir tusa basin..." << endl;
	getch();
	return;
}

//	kayitli personellerin listesini yazdirir
void personelListesi() {
	dosya.open("personel.txt", ios::app | ios::in | ios::out);
	dosya >> test;
	system("CLS");
	if (dosya.eof()) {
		cout << "Kayit yok." << endl;
	}
	else {
		dosya.close();
		dosya.open("personel.txt", ios::app | ios::in | ios::out);
		cout << setw(60) << "PERSONEL LISTESI" << endl
			 << setw(11) << "TC NO"
			 << setw(10) << "AD"
			 << setw(10) << "SOYAD"
			 << setw(8) << "UNVAN"
			 << setw(10) << "SICIL NO"
			 << setw(15) << "DOG TARIHI"
			 << setw(15) << "BOLUM"
			 << setw(10) << "ISB.YIL"
			 << setw(20) << "VERDIGI DERSLER" << endl;
		while (!dosya.eof()) {
			dosya >> tcNo >> ad >> soyad >> unvan >> sicilNo >> dogTarihi >> bolum
				  >> iseBaslamaTarihi >> verdigiDersler;
			cout << setw(11) << tcNo
				 << setw(10) << ad
				 << setw(10) << soyad
				 << setw(8) << unvan
				 << setw(10) << sicilNo
				 << setw(15) << dogTarihi
				 << setw(15) << bolum
				 << setw(10) << iseBaslamaTarihi
				 << setw(20) << verdigiDersler << endl;
		}
	}
	dosya.close();
	cout << "\n\nAna menuye donmek icin bir tusa basin..." << endl;
	getch();
	return;
}

//	bir tc yalniz bir kiside olabilir
bool tcSorgu(string sorgulanacakTc) {
	fstream nesne;
	nesne.open("ogrenci.txt", ios::app | ios::in | ios::out);
	while (!nesne.eof()) {	// dosya sonuna kadar tc no oku ve sorgula
		nesne >> test;
		if (test == sorgulanacakTc) return false;	// varsa false dondur
	}
	nesne.close();
	nesne.open("personel.txt", ios::app | ios::in | ios::out);
	while (!nesne.eof()) {	// dosya sonuna kadar tc no oku ve sorgula
		nesne >> test;
		if (test == sorgulanacakTc) return false;	// varsa false dondur
	}
	nesne.close();
	return true;	// yoksa true dondur
}
