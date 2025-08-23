#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <numeric>

namespace py = pybind11;

// Global get_mean fonksiyonu, sınıfın dışında tanımlanmalı
double get_mean(const std::vector<double>& data) {
    if (data.empty()) {
        return 0.0;
    }

    double sum = 0.0;
    for (double val : data) {
        sum += val;
    }

    return sum / data.size();
}

class SuperFrameDataFrame {
private:
    std::map<std::string, std::vector<double>> data;
    std::vector<std::string> columns;

public:
    py::object read_csv(const std::string& filename) {
        py::print("C++: ", filename, " dosyası okunuyor...");

        std::ifstream file(filename);
        if (!file.is_open()) {
            py::print("HATA: Dosya açılamadı!");
            return py::none();
        }

        std::string line;

        columns.clear();
        if (std::getline(file, line)) {
            line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
            std::stringstream ss(line);
            std::string column_name;
            while (std::getline(ss, column_name, ',')) {
                columns.push_back(column_name);
            }
        }
        
        data.clear();
        for (const auto& col_name : columns) {
            data[col_name] = std::vector<double>();
        }

        while (std::getline(file, line)) {
            line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
            std::stringstream ss(line);
            std::string value_str;
            int col_index = 0;
            while (std::getline(ss, value_str, ',')) {
                // Burada NaN değerlerini kontrol ediyoruz
                if (value_str.empty() || value_str == "nan" || value_str == "NaN") {
                    data[columns[col_index]].push_back(NAN);
                } else {
                    try {
                        data[columns[col_index]].push_back(std::stod(value_str));
                    } catch (const std::invalid_argument& e) {
                        py::print("C++: '", value_str, "' double'a çevrilemedi. NaN olarak işaretleniyor.");
                        data[columns[col_index]].push_back(NAN);
                    }
                }
                col_index++;
            }
        }

        py::print("C++: ", data.begin()->second.size(), " satır ve ", columns.size(), " sütun başarıyla okundu.");
        file.close();

        py::dict result;
        result["columns"] = py::cast(columns);
        result["data"] = py::cast(data);
        return result;
    }

    size_t count_nan(const std::string& column_name) {
        if (data.find(column_name) == data.end()) {
            py::print("HATA: '", column_name, "' sutunu bulunamadi.");
            return 0;
        }

        size_t nan_count = 0;
        for (double val : data.at(column_name)) {
            if (std::isnan(val)) {
                nan_count++;
            }
        }
        return nan_count;
    }

    py::object auto_preprocess() {
        py::print("C++: Veri otomatik olarak ön isleniyor...");

        for (const auto& pair : data) {
            std::string column_name = pair.first;
            std::vector<double> column_data = pair.second;
            
            double sum = 0.0;
            size_t count = 0;

            for (double val : column_data) {
                if (!std::isnan(val)) {
                    sum += val;
                    count++;
                }
            }

            if (count > 0) {
                double mean = sum / count;
                py::print("C++: '", column_name, "' sutununun ortalamasi hesaplandi: ", mean);

                for (size_t i = 0; i < data[column_name].size(); ++i) {
                    if (std::isnan(data[column_name][i])) {
                        data[column_name][i] = mean;
                        py::print("C++: '", column_name, "' sutunundaki bir NaN degeri ortalama ile dolduruldu.");
                    }
                }
            }
        }
        py::print("C++: On isleme tamamladi.");

        py::dict result;
        result["columns"] = py::cast(columns);
        result["data"] = py::cast(data);
        return result;
    }

    py::object get_column(const std::string& column_name) {
        py::print("C++: ", column_name, " sutun verisi isteniyor.");

        auto it = data.find(column_name);
        if (it != data.end()) {
            return py::cast(it->second);
        }

        py::print("HATA: ", column_name, " sutunu bulunamadi.");
        return py::none();
    }

    py::tuple shape() {
        size_t rows = 0;
        if (!columns.empty()) {
            rows = data.at(columns[0]).size();
        }
        size_t cols = columns.size();
        return py::make_tuple(rows, cols);
    }

    std::map<std::string, std::map<std::string, double>> describe() {
        std::map<std::string, std::map<std::string, double>> results;

        for (const auto& pair : data) {
            std::string column_name = pair.first;
            std::vector<double> column_data = pair.second;

            if (column_data.empty()) continue;

            double sum = 0.0;
            double min_val = std::numeric_limits<double>::infinity();
            double max_val = -std::numeric_limits<double>::infinity();
            size_t count = 0;

            for (double val : column_data) {
                if (!std::isnan(val)) {
                    sum += val;
                    min_val = std::min(min_val, val);
                    max_val = std::max(max_val, val);
                    count++;
                }
            }
            
            if (count > 0) {
                double mean = sum / count;
                
                double standard_deviation = 0.0;
                double squared_diff_sum = 0.0;
                for (double val : column_data) {
                    if (!std::isnan(val)) {
                        squared_diff_sum += (val - mean) * (val - mean);
                    }
                }
                if (count > 1) {
                    standard_deviation = std::sqrt(squared_diff_sum / (count - 1));
                }

                std::map<std::string, double> stats;
                stats["count"] = count;
                stats["mean"] = mean;
                stats["std"] = standard_deviation;
                stats["min"] = min_val;
                stats["max"] = max_val;
                
                results[column_name] = stats;
            }
        }
        return results;
    }
    SuperFrameDataFrame filter_by(const std::string& column_name, double value) {
    SuperFrameDataFrame new_df;
    auto it = data.find(column_name);
    if (it == data.end()) {
        py::print("HATA: '", column_name, "' sutunu bulunamadi.");
        return new_df;
    }

    const auto& column_data = it->second;
    for (const auto& col : columns) {
        new_df.data[col] = std::vector<double>();
        new_df.columns.push_back(col);
    }

    for (size_t i = 0; i < column_data.size(); ++i) {
        if (column_data[i] == value) {
            for (const auto& col : columns) {
                new_df.data[col].push_back(data.at(col)[i]);
            }
        }
    }
    return new_df;
}
};

PYBIND11_MODULE(superframe_core, m) {
    m.doc() = "SuperFrame'in C++ ile yazılmış performans çekirdeği.";
    
    py::class_<SuperFrameDataFrame>(m, "SuperFrameDataFrame")
        .def(py::init<>())
        .def("read_csv", &SuperFrameDataFrame::read_csv)
        .def("auto_preprocess", &SuperFrameDataFrame::auto_preprocess)
        .def("get_column", &SuperFrameDataFrame::get_column)
        .def("describe", &SuperFrameDataFrame::describe)
        .def("shape", &SuperFrameDataFrame::shape)
        .def("count_nan", &SuperFrameDataFrame::count_nan)
        .def("filter_by", &SuperFrameDataFrame::filter_by);

    m.def("get_mean", &get_mean, "Get the mean of the specified column.");
    
    m.def("merhaba_superframe", []() { 
        py::print("SuperFrame'in C++ çekirdeği çalışıyor!");
    });
}