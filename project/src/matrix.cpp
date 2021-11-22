#include "matrix.h"
#include "exceptions.h"

namespace prep {
    Matrix::Matrix(size_t rows, size_t cols) {
        m_rows = rows;
        m_cols = cols;
        matrix.resize(rows);
        for (size_t i = 0; i < rows; ++i) {
            matrix[i].resize(cols);
        }
    }

    Matrix::Matrix(std::istream& is) {
        try {
            if (is.bad() || is.eof()) {
                InvalidMatrixStream error;
                throw error.what();
            }
        } catch (const char* err_msg) {
            std::cout << err_msg;
        }

        is >> m_rows;
        is >> m_cols;

        matrix.resize(m_rows);

        for (size_t i = 0; i < m_rows; ++i) {
            matrix[i].resize(m_cols);
            for (size_t g = 0; g < m_cols; ++g) {
                if (!(is >> matrix[i][g])) {
                    throw InvalidMatrixStream();
                }
            }
        }
    }

    size_t Matrix::getRows() const {
        return m_rows;
    }

    size_t Matrix::getCols() const {
        return m_cols;
    }

    double Matrix::operator()(size_t i, size_t j) const {
        if (i >= m_rows || j >= m_cols) {
            throw OutOfRange(i, j, *this);
        }

        return matrix[i][j];
    }

    double& Matrix::operator()(size_t i, size_t j) {
        if (i >= m_rows || j >= m_cols) {
            throw OutOfRange(i, j, *this);
        }
        return (this -> matrix[i][j]);
    }

    bool Matrix::operator==(const Matrix& rhs) const {
        if (this -> m_rows != rhs.m_rows || this -> m_cols != rhs.m_cols) {
            return false;
        }
        for (size_t i = 0; i < rhs.m_rows; ++i) {
            for (size_t j = 0; j < rhs.m_cols; ++j) {
                if (std::fabs(this -> matrix[i][j] - rhs.matrix[i][j]) >= 1e-07) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Matrix::operator!=(const Matrix& rhs) const {
        if (*this == rhs) {
            return false;
        }
        return true;
    }

    std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        int p = std::numeric_limits<double>::max_digits10;
        os << matrix.m_rows << ' ' << matrix.m_cols << std::endl;

        for (size_t i = 0; i < matrix.m_rows; ++i) {
            for (size_t j = 0; j < matrix.m_cols; ++j) {
                os << std::setprecision(p) << matrix.matrix[i][j] << ' ';
            }
            os << std::endl;
        }
        return os;
    }

    Matrix Matrix::operator+(const Matrix& rhs) const {
        if (this -> m_rows != rhs.m_rows || this -> m_cols != rhs.m_cols) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix sum_m(m_rows, m_cols);

        for (size_t i = 0; i < rhs.m_rows; ++i) {
            for (size_t j = 0; j < rhs.m_cols; ++j) {
                sum_m.matrix[i][j] = this -> matrix[i][j] + rhs.matrix[i][j];
            }
        }

        return sum_m;
    }

    Matrix Matrix::operator-(const Matrix& rhs) const {
        if (this -> m_rows != rhs.m_rows || this -> m_cols != rhs.m_cols) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix sub_m(m_rows, m_cols);

        for (size_t i = 0; i < rhs.m_rows; ++i) {
            for (size_t j = 0; j < rhs.m_cols; ++j) {
                sub_m.matrix[i][j] = this -> matrix[i][j] - rhs.matrix[i][j];
            }
        }

        return sub_m;
    }

    Matrix Matrix::operator*(const Matrix& rhs) const {
        if (this -> m_cols != rhs.m_rows) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix mul_m(this -> m_rows, rhs.m_cols);

        for (size_t i = 0; i < mul_m.m_rows; ++i) {
            for (size_t g = 0; g < mul_m.m_cols; ++g) {
                mul_m.matrix[i][g] = 0;
            }
        }

        for (size_t k = 0; k < (rhs.m_cols); ++k) {
            for (size_t i = 0; i < (this -> m_rows); ++i) {
                for (size_t g = 0; g < (this -> m_cols); ++g) {
                    mul_m.matrix[i][k] += (this -> matrix[i][g]) * (rhs.matrix[g][k]);
                }
            }
        }

        return mul_m;
    }

    Matrix Matrix::transp() const {
        Matrix transp_m(m_cols, m_rows);

        for (size_t i = 0; i < transp_m.m_rows; ++i) {
            for (size_t g = 0; g < transp_m.m_cols; ++g) {
                transp_m.matrix[i][g] = this -> matrix[g][i];
            }
        }

        return transp_m;
    }

    Matrix Matrix::operator*(double val) const {
        Matrix res_m(m_rows, m_cols);

        for (size_t i = 0; i < res_m.m_rows; ++i) {
            for (size_t g = 0; g < res_m.m_cols; ++g) {
                res_m.matrix[i][g] = (this -> matrix[i][g]) * val;
            }
        }

        return res_m;
    }

    Matrix operator*(double val, const Matrix& matrix) {
        Matrix res_m(matrix.m_rows, matrix.m_cols);

        for (size_t i = 0; i < res_m.m_rows; ++i) {
            for (size_t g = 0; g < res_m.m_cols; ++g) {
                res_m.matrix[i][g] = (matrix.matrix[i][g]) * val;
            }
        }

        return res_m;
    }

    double Matrix::det() const {
        return (this -> matrix[0][0]);
    }

    Matrix Matrix::adj() const {
        return *this;
    }

    Matrix Matrix::inv() const {
        return *this;
    }
}  // namespace prep
