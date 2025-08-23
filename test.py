import superframe_core

# Bir SuperFrameDataFrame nesnesi oluşturun
df = superframe_core.SuperFrameDataFrame()

# CSV dosyasını okuyun
# (Dosya adını kendi dosyanızla değiştirin)
df.read_csv("veriler.csv")

# Veri çerçevesinin boyutunu al
rows, cols = df.shape()

# Sonucu yazdır
print(f"Veri setinin boyutu: {rows} satır, {cols} sütun")