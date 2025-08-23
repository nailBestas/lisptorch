import superframe_core
import pandas as pd

# Veri setini pandas ile oluştur ve CSV'ye yaz
data = {'Ad': ['Ahmet', 'Ayşe', 'Mehmet', 'Fatma', 'Can'],
        'Yaş': [25, 30, 22, 28, 35],
        'Boy': [170, 165, float('nan'), 175, 180]}
df_pandas = pd.DataFrame(data)
df_pandas.to_csv("veriler_nan.csv", index=False)

# SuperFrame ile CSV dosyasını oku
df_superframe = superframe_core.SuperFrameDataFrame()
df_superframe.read_csv("veriler_nan.csv")

# NaN değerleri say
nan_sayisi = df_superframe.count_nan("Boy")

print(f"Boy sütunundaki eksik değer sayısı: {nan_sayisi}")