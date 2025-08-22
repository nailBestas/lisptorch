# SuperFrame v0.1.0

C++ ile hızlandırılmış, Python için basit ve güçlü bir veri analizi kütüphanesi.

SuperFrame, büyük veri setlerini işlemek için Python'ın kullanım kolaylığını C++'ın yüksek performansıyla birleştirir. Bu proje, veri okuma, ön işleme ve temel istatistiksel analiz gibi işlemleri hızlandırmayı hedefler.

## Özellikler

* **Yüksek Performanslı CSV Okuma**: Verileri diskten C++ hızıyla okur.
* **Otomatik Ön İşleme**: Eksik (`NaN`) değerleri sütun ortalamalarıyla otomatik olarak doldurur.
* **Temel İstatistiksel Özet**: `describe()` fonksiyonu ile veri setinize hızlı bir genel bakış sağlar.

## Kurulum

Bu kütüphaneyi kullanmak için öncelikle C++ derleyicinizin (g++) ve Python ortamınızın kurulu olduğundan emin olun. Ardından, projenin ana dizininde aşağıdaki komutu çalıştırın:

bash
pip install .
## Kullanim
#python >>

import superframe_core
df = superframe_core.SuperFrameDataFrame()
df.read_csv("veriler.csv") 
stats = df.describe()
print(stats)

## Katkıda Bulunma
Proje hala geliştirme aşamasındadır ve katkılarınıza açıktır. Her türlü hata raporu, özellik önerisi veya kod katkısı memnuniyetle karşılanır.
