// ������ OpenCV: 4.9.0
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <conio.h>

using namespace std;
using namespace cv; // ������������ ��� ��� ������� ���������� OpenCV.

// ���������� ��� ������������� �����������.
Mat image;     
// ����������, ���������� ����������� �����������. �������������� � ������ hsv.  
Mat image_temp;
// ������, ���������� ���� � �����������.
string image_name;  
// ������, ���������� ��������� hsv ������������ �����������.
vector <Mat> hsv0;
// ������, ���������� ��������� hsv ��� ����������� �� ����� ���������.
vector <Mat> hsv;   

// ������ ��������. ������������ ��� ��������.
vector <string> formats = {"bmp","jpg","png","tif","pbm","ras"};
// �������� ����, ����������� �����������.
string window_name_image = "�����������";
// �������� ����, ����������� ���������.
string window_name_parameters = "��������� �����������"; 
// ������, ��������� � ����������.
char key;  

// ��������� ����������� �������.
void image_get();
string image_name_input(string name);
void return_to_menu();

// ������� ������ ����. ��������� ��������������� ������� ��������� ���������.
void menu()
{
    // ����� ���������� � �������� � ����.
    cout << "'1' - ������� ���� � �����������;" << endl;
    cout << "'2' - ���������� �����������;" << endl; 
    cout << "'0' - ��������� ���������." << endl;

    // ��������� ������� ������� � ����������
    key = _getch();
    // ������� ��������� ������
    system("cls");

    switch (key)
    {
    case '1': 
        image_name = image_name_input(image_name); 
        return_to_menu(); 
        break;
    case '2': 
        image_get(); 
        return_to_menu(); 
        break;
    case '0': 
        exit(0);  // ���������� ���������.
    default:
        system("cls");
        cout << "����������� ������ �����. ���������� ��� ���." << endl;
        menu();
    }
}

// ������� ����������� � ���� ���������. 
// ���������� ��� ���������� ������ �������.
void return_to_menu()
{
    cout << "\n��� ����������� � ���� ������� ����� �������: ";
    _getch();
    system("cls");
    menu();
}

// ������� ����� ���� �����������.
string image_name_input(string name)
{
    string file_type;
    bool file_type_check = false;

    cout << "������� ���� � �����:" << endl;
    cin >> name;

    // ��������, ���������� �� ���� �� ��������� ����. 
    // ���� ����� �� ����������, �� ���� �����������.
    ifstream filepath;
    filepath.open(name);

    while (filepath.fail())
    {
        cout << "\n������ � ���� �����. ��������� ����." << endl;
        cin >> name;
        filepath.open(name);
    }
    filepath.close();

    // �������� ������� �����. 
    // ���� ���� �� �������� ������������, �� ���� �����������. 
    do
    {
        // ��������� ������� ����� ������ �� ���������� ����.
        file_type = name.substr(name.length() - 3, 3);

        // ��������� ������� ����� � ���������� ������� �������� formats.
        for (int i = 0; i < formats.size(); i++)
        {
            if (file_type == formats[i])
            {
                file_type_check = true;
                break;
            }
        }

        // ���� ������ ����������� � formats, �� ��������� ���������. 
        // ���� �����������.
        if (file_type_check == false)
        {
            cout << "\n���� ����� ������������ ������. ��������� ����." << endl;
            cin >> name;
        }

    } while (file_type_check == false);

    return name;
}

// �������, ����������� ���������� ����������� � image_temp.
// image_temp �������������� � ������ hsv � �����������.
void get_hsv()
{
    image_temp = image;
    cvtColor(image, image_temp, ColorConversionCodes::COLOR_RGB2HSV);
    split(image_temp, hsv0);
}

// ������ � ��������� ����������� �� ��������� ����.
void image_get()
{
    // ���� ���� �� �����, �� ������������ ������������ � ����.
    if (image_name.empty())
    {
        cout << "�� ����� ���� � �����. ������� ���� � ���������." << endl;
        return_to_menu();
    }

    // ��������. ���������� ��� ��������� ������������ �������������.
    float precission = 0.01f;
    // ����������� �������������.
    float contrastValue;

    image = imread(image_name);
    get_hsv();

    // �������� ���� "�����������".
    namedWindow(window_name_image, WINDOW_NORMAL);

    // �������� ���� "��������� �����������".
    // �������� ������� ��������� � ��������� ����.
    // �������� �������� �� ��������� �����, ������������, ������� � ���������.
    namedWindow(window_name_parameters, WINDOW_NORMAL);
    resizeWindow(window_name_parameters, 400, 100);
    createTrackbar("����", window_name_parameters, 0, 180);
    createTrackbar("������������", window_name_parameters, 0, 255);
    createTrackbar("�������", window_name_parameters, 0, 255);
    createTrackbar("��������", window_name_parameters, 0, 500);

    // ��������� ��������� �������� ���������.
    // ��� �������� "����" �������� �� ��������� ����� ����� 0.
    // ��� ��������� "������������" � "�������" �������� ��������� �������� 127.
    // ��� �������� "��������" ��������� �������� ����� 100.
    setTrackbarPos("������������", window_name_parameters, 127);
    setTrackbarPos("�������", window_name_parameters, 127);
    setTrackbarPos("��������", window_name_parameters, 100);

    system("cls");
    cout << "��� ����������� � ���� ������� 1.";

    // ����������� �����������. 
    while (true)
    {
        // ����� ����������� � ���� "�����������".
        imshow(window_name_image, image);

        // ��� ������� ������� "1" ��� ���� �����������, ����������� ������� � ����.
        key = waitKey('1');
        if (key == '1')
        {
            system("cls");
            destroyAllWindows();
            menu();
        }

        // ������� ����������� � �������� ������ hsv. 
        // ����������� ����������� �� ��������� hsv.
        // ��������� ����������� � �������� �������.
        cvtColor(image, image, ColorConversionCodes::COLOR_BGR2HSV);
        split(image, hsv);
        hsv[0] = hsv0[0] + getTrackbarPos("����", window_name_parameters);
        hsv[1] = hsv0[1] + getTrackbarPos("������������", window_name_parameters) - 127;
        hsv[2] = hsv0[2] + getTrackbarPos("�������", window_name_parameters) - 127;

        // ����������� ���������� �� ���������� hsv,
        // ����� ������������� ������� � ������ rgb.
        merge(hsv, image);
        cvtColor(image, image, ColorConversionCodes::COLOR_HSV2RGB);

        // �������� �������������. 
        // ������� �� ��������� ���������������� �������� ����������� �� ����������� 0,01.
        contrastValue = getTrackbarPos("��������", window_name_parameters) * precission;
        image = image * contrastValue;
    }
}

int main()
{
    // ��������� �������� �����.
    setlocale(LC_ALL, "Rus");
    
    // ����� ������� menu.
    menu();
}