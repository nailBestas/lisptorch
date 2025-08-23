import superframe_core
import pandas as pd

# Veri setini pandas ile oluştur ve CSV'ye yaz
data = {'Ad': ['Ahmet', 'Ayşe', 'Mehmet', 'Fatma', 'Can'],
        'Yaş': [25, 30, 22, 30, 35],
        'Boy': [170, 165, 175, 165, 180]}
df_pandas = pd.DataFrame(data)
df_pandas.to_csv("veriler_filter.csv", index=False)

# SuperFrame ile CSV dosyasını oku
df_superframe = superframe_core.SuperFrameDataFrame()
df_superframe.read_csv("veriler_filter.csv")

# Yaşı 30 olanları filtrele
filtered_df = df_superframe.filter_by("Yaş", 30)

# Filtrelenen veriyi kontrol etmek için boyutu yazdır
rows, cols = filtered_df.shape()
print(f"Filtrelenen veri setinin boyutu: {rows} satır, {cols} sütun")

# Filtrelenen veriyi konsola yazdır
filtered_data = filtered_df.get_column("Ad")
print(f"Filtrelenen 'Ad' sütunu: {filtered_data}")