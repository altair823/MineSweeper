#include "MineField.h"

_intArray::_intArray(int size) {
    // ������ �迭�� ����ִٸ� ���� ����
    if (data.size() == 0) {
        data.resize(size);
    }
    // ������ �迭�� ������� �ʴٸ� ����. ���� �ʱ�ȭ�� �ؾ���. 
    else {
        std::cout << "�ʱ�ȭ���� ���� ���� ���� �����Ǿ����ϴ�." << std::endl;
        exit(1);
    }
}

int& const _intArray::operator[](const int index) {
    if (index >= data.size()) {
        std::cout << "data �࿡�� ���� �ʰ� ������ �߻��߽��ϴ�. \ngiven index: " << index << ", current vector size: " << data.size() << std::endl;
        exit(1);
    }
    else {
        return data[index];
    }
}

void _intArray::Clear() {
    data.clear();
}

void _intArray::Resize(int size) {
    this->Clear();
    data.resize(size);
}



_intArray& const MineField::operator[](const int index) {
    if (index >= fieldData.size()) {
        std::cout << "data �࿡�� ���� �ʰ� ������ �߻��߽��ϴ�. \ngiven index: " << index << ", current vector size: " << fieldData.size() << std::endl;
        exit(1);
    }
    else {
        return fieldData[index];
    }
}

void MineField::Clear() {
    // ��� �� �ʱ�ȭ
    for (auto& row : fieldData) {
        row.Clear();
    }

    // ����� ���� �ʱ�ȭ
    fieldData.clear();
}

void MineField::Resize(int newRow, int newCol) {
    row = newRow;
    col = newCol;
    for (int i = 0; i < newRow; i++) {
        // col ũ���� �� ���͸� �������� �����ϰ� �̸� fieldData�� ����
        auto rowData(newCol);
        fieldData.push_back(rowData);
    }

    // ������ ������ ��ü ĭ���� 1/4
    // �ʿ��ϴٸ� ���氡��
    mineCount = newRow * newCol / 4;
}

void MineField::MountMine() {
    srand((unsigned int)time(NULL));

    // ��ƾ��� ���� ������ŭ �ݺ��Ѵ�. 
    for (int i = 0; i < mineCount;) {
        // �������� ��ġ ����
        int curRow = rand() % row;
        int curCol = rand() % col;
        // ���� �̹� ���ڰ� �� �ڸ��� ���õȴٸ� �ٽ� �����Ѵ�. 
        if (fieldData[curRow][curCol] == CellValue::Mine) {
            continue;
        }
        fieldData[curRow][curCol] = CellValue::Mine;
        i++;
    }
}

void MineField::setRandomValue() {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            fieldData[i][j] = rand() % 10;
        }
    }
}

void MineField::Print() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (fieldData[i][j] == CellValue::Mine) {
                std::cout << "* ";
            }
            else {
                std::cout << fieldData[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

void MineField::setAdjacentNum() {
    // ��� �� ��ȸ
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            // ����ĭ�� �ǳ� ��
            if (fieldData[i][j] == CellValue::Mine) {
                continue;
            }
            // ������ ������ ����
            int adjacentMineCount = 0;

            // �� �� ��ȸ
            for (int adjacentRow = i - 1; adjacentRow <= i + 1; adjacentRow++) {
                // �� �� ��ȸ
                for (int adjacentCol = j - 1; adjacentCol <= j + 1; adjacentCol++) {
                    // �� �Ǵ� �� ���� ������ ����� �ش� ������ ���� ���캸�� �ʴ´�. 
                    if (adjacentRow < 0 || adjacentCol < 0 || adjacentRow > row - 1 || adjacentCol > col - 1) {
                        continue;
                    }
                    // ������ ���� ���ڰ� �ִٸ� ���� +1
                    if (fieldData[adjacentRow][adjacentCol] == CellValue::Mine) {
                        adjacentMineCount++;
                    }
                }
            }

            // ������ ������ ������ ���� �ٲ۴�.
            fieldData[i][j] = adjacentMineCount;
        }
    }
}
