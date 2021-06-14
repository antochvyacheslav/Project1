#pragma once

//������� 3 ������.
//���������� ������� ������������ � �������������� ����������� ������ � �������� ������� � ����.��������������� ��������� ������� ������ ���� ������ ������������.
//����������: ������������ ������������� ���������� � �������������� ������ ��������� ������, ������� �������� ����������� ��� ��������� ����� �����.

//��� ���������� �� 3 ������:
//!1. ��� ���������� ������ ��������� ������, ������� �������� ������������ ��� ��������� ����� ����� ����� �������������� ����������� ���������� ������� �����,
//! �������, ��� ��������� ���� List �� ��������������� ����������� ������� �� �������, ������� ���������� ���������� ������� ����� ������������ ������ ��� ������������/�������������� ��� ���������� � �������������� ������ ��������� ������,
//! �.�. ���������� ������������ ������� ����� �� ������ ������������/��������������, ����� ���������/������������ ������� ��������� ������ ������ � ��� ��� �������.
//!2. ����� ���������� ������ � ����� ������ (AddToEnd) ������ ��������, ������ ��� ��� �������� ����� �������� �����-�� �������� ������, � ��� ������� ����� ����������� ��-������ - list1.AddToEnd("_a_");
//! �� ����� ����� ���������� ����� ��� ��������������, � ��� ��� � ������� ��������� ��������� �� ������ string, � �.�. ��� � ����� ������� ����������, � ���������� ������ ����������� ������ data, �� �����, 
//! ��� ����� �������� ������� �����, ���� ������� ������ �������, ��� ����������� ������ ������ ���������� ��������� ���������� ��� ����������� ����� SetData � ���������� ���, ������� �� ���������� ������ ���������� �������� data
//!3. ��� ������������ � ������������� ��������� ������ ������������ (��� ����� �� ���� �����, ������ �������� ������ ���� ���� ��������� ��� ����)
//! *��� ����������� ��� ��������� ������ ��������� �� ������������ ������� ������ �������� ��������� map, ������� ������ ���� ��������� �� ���� � ���������� ����� ����
//! *��� �������������� ��� �������������� ��������� �� ��������� ������� ������ ��������� ��� ���������� ���� vector, ���� ��� �������� ���������� �� ����, ������ ��� �������� ���������� ������� ��������� �����
//!4. ������ � ������� ��� �������������� - ��� ���������� ������ (string) �� �����, ������ ������ ���������� ���� ���, ����� ��� ����������� � ������ � ������� ��������� ����������� (move)

#include "List.h"