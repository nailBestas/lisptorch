#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath> // NAN değerini kullanmak için gerekli

namespace py = pybind11;

// DataFrame benzeri veri yapımız
class SuperFrameDataFrame {
public:
    // Veriyi tutacak matris yapısı (satırlar ve sütunlar)
    std::vector<std::vector<double>> data;
    // Sütun isimlerini tutacak vektör
    std::vector<std::string> columns;

    // CSV dosyasını okuyacak fonksiyon
    py::object read_csv(const std::string& filename) {
        py::print("C++: ", filename, " dosyası okunuyor...");

        std::ifstream file(filename);
        if (!file.is_open()) {
            py::print("HATA: Dosya açılamadı!");
            return py::none();
        }

        std::string line;
        
        // Sütun isimlerini oku (ilk satır)
        if (std::getline(file, line)) {
            line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
            std::stringstream ss(line);
            std::string column_name;
            while (std::getline(ss, column_name, ',')) {
                columns.push_back(column_name);
            }
        }

        // Veri satırlarını oku
        while (std::getline(file, line)) {
            line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
            std::stringstream ss(line);
            std::string value_str;
            std::vector<double> row;
           while (std::getline(ss, value_str, ',')) {
            try {
                // Değeri double'a çevir
                row.push_back(std::stod(value_str));
            } catch (const std::invalid_argument& e) {
                // Eğer çevrilemezse NaN olarak işaretle
                py::print("C++: '", value_str, "' double'a çevrilemedi. NaN olarak işaretleniyor.");
                row.push_back(NAN);
            }
        }
            data.push_back(row);
        }
        
        py::print("C++: ", data.size(), " satır ve ", columns.size(), " sütun başarıyla okundu.");
        file.close();

        // Veriyi Python'a döndür
        py::dict result;
        result["columns"] = py::cast(columns);
        result["data"] = py::cast(data);
        
        return result;
    }

    // Otomatik ön işleme fonksiyonu
   
    // Otomatik ön işleme fonksiyonu
    py::object auto_preprocess() {
        py::print("C++: Veri otomatik olarak ön isleniyor...");

        for (size_t i = 0; i < columns.size(); ++i) {
            double sum = 0.0;
            size_t count = 0;
            
            for (size_t j = 0; j < data.size(); ++j) {
                if (!std::isnan(data[j][i])) {
                    sum += data[j][i];
                    count++;
                }
            }
            
            if (count > 0) {
                double mean = sum / count;
                py::print("C++: '", columns[i], "' sutununun ortalamasi hesaplandi: ", mean);

                for (size_t j = 0; j < data.size(); ++j) {
                    if (std::isnan(data[j][i])) {
                        data[j][i] = mean;
                        py::print("C++: '", columns[i], "' sutunundaki bir NaN degeri ortalama ile dolduruldu.");
                    }
                }
            }
        }
        py::print("C++: On isleme tamamladi.");
        
        // GÜNCELLENMİŞ VERİYİ PYTHON'A DÖNDÜR
        py::dict result;
        result["columns"] = py::cast(columns);
        result["data"] = py::cast(data);
        return result;
    }
    
    // Sütun ismine göre veriyi getiren fonksiyon
    py::object get_column(const std::string& column_name) {
        py::print("C++: ", column_name, " sutun verisi isteniyor.");

        for (size_t i = 0; i < columns.size(); ++i) {
            // Sütun isimlerini karşılaştırırken başındaki ve sonundaki boşlukları temizle
            std::string cleaned_column_name = columns[i];
            cleaned_column_name.erase(cleaned_column_name.find_last_not_of(" \t\n\r\f\v") + 1);
            if (cleaned_column_name == column_name) {
                std::vector<double> column_data;
                for (size_t j = 0; j < data.size(); ++j) {
                    column_data.push_back(data[j][i]);
                }
                return py::cast(column_data);
            }
        }
        
        py::print("HATA: ", column_name, " sutunu bulunamadi.");
        return py::none();
    }
};

// PYBIND11_MODULE fonksiyonu, C++ sınıfını Python'a açar
PYBIND11_MODULE(superframe_core, m) {
    m.doc() = "SuperFrame'in C++ ile yazılmış performans çekirdeği.";
    
    // SuperFrameDataFrame sınıfını Python'a tanımlıyoruz
    py::class_<SuperFrameDataFrame>(m, "SuperFrameDataFrame")
        .def(py::init<>())
        .def("read_csv", &SuperFrameDataFrame::read_csv)
        .def("auto_preprocess", &SuperFrameDataFrame::auto_preprocess)
        .def("get_column", &SuperFrameDataFrame::get_column);
    
    // Önceki denememizdeki merhaba_superframe fonksiyonu
    m.def("merhaba_superframe", []() { 
        py::print("SuperFrame'in C++ çekirdeği çalışıyor!");
    });
}