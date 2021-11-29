#include "MineField.h"

_fieldDataArray::_fieldDataArray(int size) {
    // ������ �迭�� ����ִٸ� ���� ����
    if (data.size() == 0) {
        data.resize(size);
        for (auto& i : data) {
            i.cellValue = CellValue::Empty;
            i.itemValue = ItemValue::None;
        }
    }
    // ������ �迭�� ������� �ʴٸ� ����. ���� �ʱ�ȭ�� �ؾ���. 
    else {
        std::cout << "�ʱ�ȭ���� ���� ���� ���� �����Ǿ����ϴ�." << std::endl;
        exit(1);
    }
}

FieldData& const _fieldDataArray::operator[](const int index) {
    if (index >= data.size()) {
        std::cout << "data �࿡�� ���� �ʰ� ������ �߻��߽��ϴ�. \ngiven index: " << index << ", current vector size: " << data.size() << std::endl;
        exit(1);
    }
    else {
        return data[index];
    }
}

void _fieldDataArray::Clear() {
    data.clear();
}

void _fieldDataArray::Resize(int size) {
    this->Clear();
    data.resize(size);
    for (auto& i : data) {
        i.cellValue = CellValue::Empty;
    }
}



_fieldDataArray& const MineField::operator[](const int index) {
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
    // �ʱ�ȭ
    for (int i = 0; i < row; i++) {
        fieldData[i].Clear();
    }
    fieldData.clear();

    // resize
    row = newRow;
    col = newCol;
    for (int i = 0; i < newRow; i++) {
        // col ũ���� �� ���͸� �������� �����ϰ� �̸� fieldData�� ����
        _fieldDataArray rowData(newCol);
        fieldData.push_back(rowData);
    }

    // ������ ������ ��ü ĭ���� 1/6
    // �ʿ��ϴٸ� ���氡��
    mineCount = newRow * newCol / 6;
}

void MineField::MountMine() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> randRow(0, row - 1);
    std::uniform_int_distribution<int> randCol(0, col - 1);


    // ���� ����
    for (int i = 0; i < mineCount;) {
        // �������� ��ġ ����
        int curRow = randRow(gen);
        int curCol = randCol(gen);
        // ���� �̹� ���ڰ� �� �ڸ��� ���õȴٸ� �ٽ� �����Ѵ�. 
        if (fieldData[curRow][curCol].cellValue == CellValue::Mine) {
            continue;
        }
        fieldData[curRow][curCol].cellValue = CellValue::Mine;
        i++;
    }

    // Ż�ⱸ ����
    for (int i = 0; i < 1;) {
        int curRow = randRow(gen);
        int curCol = randCol(gen);
        if (fieldData[curRow][curCol].cellValue != CellValue::Empty) {
            continue;
        }
        fieldData[curRow][curCol].cellValue = CellValue::Escape;
        i++;
    }

    // ������ ����
    // ���� Ž����
    for (int i = 0; i < MINE_DETECTOR_COUNT;) {
        int curRow = randRow(gen);
        int curCol = randCol(gen);
        if (fieldData[curRow][curCol].cellValue != CellValue::Empty
            || fieldData[curRow][curCol].itemValue != ItemValue::None) {
            continue;
        }
        fieldData[curRow][curCol].itemValue = ItemValue::MineDetector;
        i++;
    }
    // ���� ȸ��
    for (int i = 0; i < AVOID_COMBAT_COUNT;) {
        int curRow = randRow(gen);
        int curCol = randCol(gen);
        if (fieldData[curRow][curCol].cellValue != CellValue::Empty
            || fieldData[curRow][curCol].itemValue != ItemValue::None) {
            continue;
        }
        fieldData[curRow][curCol].itemValue = ItemValue::AvoidCombat;
        i++;
    }
    // ��� +1 
    for (int i = 0; i < ADDLIFE_COUNT;) {
        int curRow = randRow(gen);
        int curCol = randCol(gen);
        if (fieldData[curRow][curCol].cellValue != CellValue::Empty
            || fieldData[curRow][curCol].itemValue != ItemValue::None) {
            continue;
        }
        fieldData[curRow][curCol].itemValue = ItemValue::AddLife;
        i++;
    }
}

void MineField::setAdjacentNum() {
    // ��� �� ��ȸ
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            // ����ĭ�� �ǳ� ��
            if (fieldData[i][j].cellValue == CellValue::Mine) {
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
                    if (fieldData[adjacentRow][adjacentCol].cellValue == CellValue::Mine) {
                        adjacentMineCount++;
                    }
                }
            }

            // ������ ������ ������ ���� �ٲ۴�.
            fieldData[i][j].num = adjacentMineCount;
        }
    }
}
