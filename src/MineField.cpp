#include "MineField.h"

_fieldDataArray::_fieldDataArray(int size) {
    // 데이터 배열이 비어있다면 새로 생성
    if (data.size() == 0) {
        data.resize(size);
        for (auto& i : data) {
            i.cellValue = CellValue::Empty;
            i.itemValue = ItemValue::None;
        }
    }
    // 데이터 배열이 비어있지 않다면 오류. 먼저 초기화를 해야함. 
    else {
        std::cout << "초기화되지 않은 행이 새로 생성되었습니다." << std::endl;
        exit(1);
    }
}

FieldData& const _fieldDataArray::operator[](const int index) {
    if (index >= data.size()) {
        std::cout << "data 행에서 범위 초과 오류가 발생했습니다. \ngiven index: " << index << ", current vector size: " << data.size() << std::endl;
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
        std::cout << "data 행에서 범위 초과 오류가 발생했습니다. \ngiven index: " << index << ", current vector size: " << fieldData.size() << std::endl;
        exit(1);
    }
    else {
        return fieldData[index];
    }
}

void MineField::Clear() {
    // 모든 행 초기화
    for (auto& row : fieldData) {
        row.Clear();
    }

    // 행들의 벡터 초기화
    fieldData.clear();
}

void MineField::Resize(int newRow, int newCol) {
    // 초기화
    for (int i = 0; i < row; i++) {
        fieldData[i].Clear();
    }
    fieldData.clear();

    // resize
    row = newRow;
    col = newCol;
    for (int i = 0; i < newRow; i++) {
        // col 크기의 새 벡터를 동적으로 생성하고 이를 fieldData에 삽입
        _fieldDataArray rowData(newCol);
        fieldData.push_back(rowData);
    }

    // 지뢰의 개수는 전체 칸수의 1/6
    // 필요하다면 변경가능
    mineCount = newRow * newCol / 6;
}

void MineField::MountMine() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> randRow(0, row - 1);
    std::uniform_int_distribution<int> randCol(0, col - 1);


    // 지뢰 생성
    for (int i = 0; i < mineCount;) {
        // 무작위로 위치 선택
        int curRow = randRow(gen);
        int curCol = randCol(gen);
        // 만약 이미 지뢰가 깔린 자리가 선택된다면 다시 선택한다. 
        if (fieldData[curRow][curCol].cellValue == CellValue::Mine) {
            continue;
        }
        fieldData[curRow][curCol].cellValue = CellValue::Mine;
        i++;
    }

    // 탈출구 생성
    for (int i = 0; i < 1;) {
        int curRow = randRow(gen);
        int curCol = randCol(gen);
        if (fieldData[curRow][curCol].cellValue != CellValue::Empty) {
            continue;
        }
        fieldData[curRow][curCol].cellValue = CellValue::Escape;
        i++;
    }

    // 아이템 생성
    // 지뢰 탐지기
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
    // 전투 회피
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
    // 목숨 +1 
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
    // 모든 셀 순회
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            // 지뢰칸은 건너 뜀
            if (fieldData[i][j].cellValue == CellValue::Mine) {
                continue;
            }
            // 인접한 지뢰의 개수
            int adjacentMineCount = 0;

            // 행 값 순회
            for (int adjacentRow = i - 1; adjacentRow <= i + 1; adjacentRow++) {
                // 열 값 순회
                for (int adjacentCol = j - 1; adjacentCol <= j + 1; adjacentCol++) {
                    // 행 또는 열 값이 범위를 벗어나면 해당 인접한 셀은 살펴보지 않는다. 
                    if (adjacentRow < 0 || adjacentCol < 0 || adjacentRow > row - 1 || adjacentCol > col - 1) {
                        continue;
                    }
                    // 인접한 셀에 지뢰가 있다면 개수 +1
                    if (fieldData[adjacentRow][adjacentCol].cellValue == CellValue::Mine) {
                        adjacentMineCount++;
                    }
                }
            }

            // 인접한 지뢰의 개수로 값을 바꾼다.
            fieldData[i][j].num = adjacentMineCount;
        }
    }
}
