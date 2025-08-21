# SuperFrame
#### C++ ile Hızlandırılmış Basit Bir Python DataFrame Kütüphanesi

## Proje Hakkında
SuperFrame, Python'ın kullanım kolaylığı ile C++'ın yüksek performansını bir araya getiren hafif bir veri işleme kütüphanesidir. Bu proje, özellikle büyük veri setlerini işlerken performans darboğazlarını aşmak için C++ dilinin gücünden faydalanan bir veri çerçevesi (DataFrame) oluşturmayı amaçlamaktadır.

Bu kütüphanenin temel amacı, Pybind11 aracıyla C++ ve Python arasındaki köprüyü nasıl kuracağımızı ve bu entegrasyonun gerçek bir veri bilimi problemine (eksik verileri işleme gibi) nasıl uygulanacağını göstermektir.

## Temel Özellikler
* **Hızlı CSV Okuma:** CSV dosyalarını C++ ile hızlı bir şekilde belleğe okur.
* **Otomatik Ön İşleme:** Sayısal olmayan veya eksik (NaN) değerleri otomatik olarak tespit eder.
* **Akıllı Doldurma (Imputation):** Eksik sayısal verileri ilgili sütunun ortalamasıyla doldurur.
* **Pybind11 ile Entegrasyon:** Python-C++ etkileşimini kolayca sağlar.

## Kurulum
SuperFrame'i yerel makinenize kurmak için aşağıdaki adımları izleyin.
* Gerekli bağımlılıkları yükleyin:
    ```bash
    pip install pybind11
    ```
* Proje dizininde (setup.py dosyasının olduğu yerde) aşağıdaki komutu çalıştırarak paketi derleyin ve kurun:
    ```bash
    pip install .
    ```

## Kullanım
SuperFrame'in temel işlevlerini kullanmak oldukça basittir.

```python
import superframe_core

# Kütüphaneyi başlat
sf = superframe_core.SuperFrameDataFrame()

# CSV dosyasını oku
# Okuma sırasında 'yok' gibi metinsel değerler NaN olarak işaretlenir.
df_data = sf.read_csv("deneme.csv")
print("Ham Veri:", df_data)

# Veriyi otomatik olarak ön işle
# Bu adımda NaN değerleri, sütun ortalaması ile doldurulur.
df_preprocessed = sf.auto_preprocess()
print("Ön İşlenmiş Veri:", df_preprocessed)

# İşlenmiş veriden bir sütun çek
yas_sutunu = sf.get_column("yas")
print("İşlenmiş 'yas' sütunu:", yas_sutunu)

Geliştirme Süreci
Bu proje, adım adım bir geliştirme süreci izleyerek oluşturulmuştur:

Pybind11 ile ilk modülün oluşturulması.

SuperFrameDataFrame sınıfının tasarlanması.

C++'ta read_csv ve get_column fonksiyonlarının implementasyonu.

auto_preprocess fonksiyonu ile akıllı ön işleme (NaN doldurma) mantığının eklenmesi.

Son kontroller ve testler.

Katkıda Bulunma
Projeye katkıda bulunmak isterseniz, pull request göndererek veya bir sorun (issue) açarak bize ulaşabilirsiniz.


### Son Adımlar

1.  Bu metni `README.md` dosyana kopyalayıp yapıştır ve kaydet.
2.  Terminali aç ve proje dizininde aşağıdaki komutları çalıştır:
    ```bash
    git add README.md
    git commit -m "README dosyası eklendi."
    git push origin main
    ```
Bu komutlar, yeni `README.md` dosyanı GitHub'a yükleyecek. Bundan sonra, deponun an
