import superframe_core

def run_superframe_demo():
    print("--- SuperFrame Demo Başlıyor ---")
    
    # 1. SuperFrameDataFrame sınıfını başlat
    sf = superframe_core.SuperFrameDataFrame()
    
    # 2. deneme.csv dosyasını oku ve veriyi işle
    print("\nAdım 1: CSV dosyasını okuma.")
    df_data = sf.read_csv("deneme.csv")
    print("Okunan ham veri:", df_data)
    
    # 3. Otomatik ön işleme yap (NaN değerlerini doldur)
    print("\nAdım 2: Otomatik ön işleme yapılıyor.")
    df_preprocessed = sf.auto_preprocess()
    print("Ön işlenmiş veri:", df_preprocessed)
    
    # 4. İşlenmiş veriden 'yas' sütununu çek
    print("\nAdım 3: İşlenmiş veriden bir sütun çekiliyor.")
    yas_sutunu = sf.get_column("yas")
    print("Çekilen 'yas' sütunu:", yas_sutunu)
    
    print("\n--- SuperFrame Demo Tamamlandı ---")

# Fonksiyonu çalıştır
run_superframe_demo()