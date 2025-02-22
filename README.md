# Syslog Analiz Programı

Bu proje, Linux işletim sistemindeki syslog kayıtlarını analiz etmek ve yönetmek için çift yönlü bağlı liste (doubly linked list) veri yapısını kullanan bir uygulamadır.

## 📌 Özellikler

Syslog kayıtlarını çift yönlü bağlı liste kullanarak saklama.

Tesis adına göre arama (örneğin: kernel, auth).

Öncelik seviyesine göre filtreleme (örneğin: 3 hata seviyesindeki kayıtları göster).

Bellek sızıntısını önlemek için listeyi temizleme işlevi.


## 🚀 Kurulum ve Çalıştırma

### 1️⃣ Derleme

Programı derlemek için aşağıdaki komutu kullanın:
```
gcc -o syslog_analyzer syslog_analyzer.c -Wall
```

### 2️⃣ Çalıştırma
```
./syslog_analyzer
```
## 📂 Dosya Yapısı
```
├── syslog_analyzer.c  # Ana C kodu
├── README.md          # Proje açıklaması
```
## 🛠 Geliştirme

Daha fazla filtreleme seçeneği eklenebilir.

Dosyadan gerçek syslog verilerini okuma özelliği eklenebilir.

