#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

template <typename T>
class Vector
{
public:
    // initCapacity la dung luong ban dau cua
    // vector, co gia tri ngan dinh bang 16
    Vector(int initCapacity = 16)
    {
        size = 0;
        capacity = initCapacity;
        array = new T[capacity];
    }
    
    ~Vector()
    {
        delete[] array;
    }
    
    // rhs (right-hand side) la vector ve phai cua phep gan.
    // this la con tro toi vector hien hanh, tuc la ve trai.
    Vector& operator=(Vector& rhs)
    {
        if (this != &rhs) // ngan can tu sao chep
        {
            delete[] array;          // xoa mang hien tai
            size = rhs.size;         // dat kich thuoc moi
            capacity = rhs.capacity; // dat dung luong moi
            array = new T[capacity]; // tao mang moi
            
            // Sao chep cac phan tu tu phai sang trai
            for (int i = 0; i < size; i++)
                array[i] = rhs.array[i];
        }
        
        return *this; // tra ve vector ve trai sau khi gan xong
    }
    
    // Tra ve kich thuoc vector
    int getSize()
    {
        return size;
    }
    
    int getCapacity()
    {
        return capacity;
    }
    
    // Tra ve true neu vector rong, nguoc lai tra ve false
    bool isEmpty()
    {
        return (size == 0);
    }
    
    // index la chi so cua phan tu can truy nhap
    T& operator[](int index)
    {
        return array[index];
    }
    
    // newElement la phan tu moi can chen vao cuoi vector
    void pushBack(T newElement)
    {
        // Gap doi dung luong neu vector day
        if (size == capacity)
            expand(2 * size);
        
        // Chen phan tu moi vao ngay sau phan tu cuoi cung
        array[size] = newElement;
        
        // Tang kich thuoc
        size++;
        if (size < capacity) balance();
    }
    
    // pos (position) la vi tri chen.
    // newElement la phan tu moi can chen.
    void insert(int pos, T newElement)
    {
        // Gap doi dung luong neu vector day
        if (size == capacity)
            expand(2 * size);
        
        // Dich cac phan tu sang phai de tao cho trong cho viec chen
        for (int i = size; i > pos; i--)
            array[i] = array[i - 1];
        
        // Dat phan tu moi vao vi tri chen
        array[pos] = newElement;
        
        // Tang kich thuoc
        size++;
        if (size < capacity) balance();
    }
    
    // Xoa phan tu o cuoi vector
    void popBack()
    {
        size--;
    }
    
    // Xoa tat ca cac phan tu
    void clear()
    {
        size = 0;
    }
    
    // pos (position) vi tri cua phan tu can xoa
    void erase(int pos)
    {
        // Dich cac phan tu sang trai de lap day cho trong de lai do viec xoa
        for (int i = pos; i < size - 1; i++)
            array[i] = array[i + 1];
        
        // Giam kich thuoc
        size--;
    }
    
private:
    int size;     // kich thuoc vector (so phan tu hien co)
    int capacity; // dung luong vector (suc chua)
    T* array;      // con tro toi mang chua cac phan tu
    
    // Day la thao tac tro giup cho cac thao tac chen.
    // newCapacity la dung luong moi (phai lon hon kich thuoc).
    void expand(int newCapacity)
    {
        if (newCapacity <= size)
            return;
        
        T* old = array;            // old tro toi mang cu
        array = new T[newCapacity]; // array tro toi mang moi
        
        for (int i = 0; i < size; i++)
            array[i] = old[i];      // sao chep phan tu tu mang cu sang mang moi
        
        delete[] old;               // xoa mang cu
        capacity = newCapacity;     // dat dung luong moi
    }
    void balance()
    {
        T* old = array;            // old tro toi mang cu
        array = new T[size]; // array tro toi mang moi
        
        for (int i = 0; i < size; i++)
            array[i] = old[i];      // sao chep phan tu tu mang cu sang mang moi
        
        delete[] old;               // xoa mang cu
        capacity = size;
    }
};

struct Student
{
    string code;
    string name;
    Student(string code, string name)
    {
        this->code = code;
        this->name = name;
    }
    Student()
    {
    }
};

Vector<Student> vtStudent;

Student getInputStudent()
{
    string code, name;
    cout << "Nhap ma sinh vien: ";
    cin >> code;
    cin.ignore();
    cout << "Nhap ten sinh vien: ";
    getline(cin, name);
    Student st = Student(code, name);
    return st;
}

void printStudent(int index)
{
    cout << "Vi tri sinh vien: " << index + 1 << endl;
    cout << "Ma sinh vien: " << vtStudent[index].code << endl;
    cout << "Ten sinh vien: " << vtStudent[index].name << endl;
}

int getIndexWithIndex()
{
    int index;
    do
    {
        cout << "Nhap thu tu sinh vien: ";
        cin >> index;
        if (index < 1 || index>vtStudent.getSize())
            cout << "Nhap thu tu lon hon 0 va khong qua " << vtStudent.getSize() << "!" << endl;
    } while (index < 1 || index>vtStudent.getSize());
    return index - 1;
}

int getIndexWithCode()
{
    string code;
    cout<< "Nhap ma sinh vien: ";
    cin>>code;
    int i;
    for (i = 0; i<vtStudent.getSize(); i++)
    {
        if(vtStudent[i].code == code)
        {
            return i;
            break;
        }
    }
    return -1;
}

void printStudentWithName()
{
    string name;
    cout<< "Nhap ten sinh vien: ";
    cin>>name;
    bool isFound = false;
    std::transform(name.begin(), name.end(),name.begin(), ::tolower);
    for (int i = 0; i<vtStudent.getSize(); i++)
    {
        string searchName=vtStudent[i].name;
        std::transform(searchName.begin(),searchName.end(),searchName.begin(), ::tolower);
        if(searchName.find(name) != string::npos)
        {
            printStudent(i);
            isFound = true;
        }
    }
    if (!isFound) {
        cout<<"Khong tim thay sinh vien nao!"<< endl;
    }
    
}

void addMultiStudent(int quantity) {
    for (int i = 0; i < quantity; i++)
    {
        cout << "Them sinh vien thu " << i + 1 << endl;
        vtStudent.pushBack(getInputStudent());
    }
}

void printAllStudent()
{
    for (int i = 0; i < vtStudent.getSize(); i++)
    {
        cout << "Sinh vien thu " << i + 1 << endl;
        cout << "Ma sinh vien: " << vtStudent[i].code << endl;
        cout << "Ten sinh vien: " << vtStudent[i].name << endl;
    }
}

void updateStudent(int index)
{
    cout<<"Cap nhat sinh vien!"<< endl;
    Student st = getInputStudent();
    vtStudent[index].code = st.code;
    vtStudent[index].name = st.name;
    cout<<"Da cap nhat sinh vien!"<< endl;
}

int main()
{
    cout << "--------------------------------" << endl;
    cout << "0.Nhan phim 0 de thoat chuong trinh" << endl;
    cout << "1.Nhan phim 1 lay so luong sinh vien" << endl;
    cout << "2.Nhan phim 2 de kiem tra co sinh vien khong" << endl;
    cout << "3.Nhan phim 3 de xem thong tin sinh vien" << endl;
    cout << "4.Nhan phim 4 de them nhieu sinh vien" << endl;
    cout << "5.Nhan phim 5 de them sinh vien" << endl;
    cout << "6.Nhan phim 6 de chen sinh vien" << endl;
    cout << "7.Nhan phim 7 sua sinh vien" << endl;
    cout << "8.Nhan phim 8 de xoa sinh vien o cuoi danh sach" << endl;
    cout << "9.Nhan phim 9 de xoa sinh vien theo vi tri" << endl;
    cout << "10.Nhan phim 10 de xem tat ca sinh vien" << endl;
    cout << "11.Nhan phim 11 lay dung luong va kich thuoc" << endl;
    cout << "--------------------------------" << endl;
    
    int option = 0;
    
    do
    {
        cout << "Moi chon chuc nang: ";
        cin >> option;
        switch (option)
        {
            case 1: //Xem so luong sinh vien
                if (vtStudent.isEmpty())
                {
                    cout << "Chua co sinh vien nao!" << endl;
                }
                else
                {
                    cout << "So luong sinh vien la: " << vtStudent.getSize() << endl;
                }
                break;
                
            case 2: //Kiem tra trong sinh vien
                if (vtStudent.isEmpty())
                {
                    cout << "Chua co sinh vien nao!" << endl;
                }
                else
                {
                    cout << "Da co sinh vien" << endl;
                }
                break;
                
            case 3: //Xem thong tin sinh vien
                if (vtStudent.isEmpty())
                {
                    cout << "Danh sach rong, moi nhap sinh vien!" << endl;
                }
                else
                {
                    cout << "--------------------------------" << endl;
                    cout << "0.Nhan phim 0 de thoat chuc nang" << endl;
                    cout << "1.Nhan phim 1 tim kiem theo vi tri" << endl;
                    cout << "2.Nhan phim 2 tim kiem theo ma sinh vien" << endl;
                    cout << "3.Nhan phim 3 tim kiem theo ten sinh vien" << endl;
                    cout << "--------------------------------" << endl;
                    int searchType;
                    int index;
                    do {
                        cout << "Moi chon kieu tim kiem: ";
                        cin >> searchType;
                        switch (searchType) {
                            case 1:
                                cout << "-------------Tim sinh vien theo thu tu--------------" << endl;
                                index = getIndexWithIndex();
                                printStudent(index);
                                break;
                            case 2:
                                cout << "-------------Tim sinh vien theo ma sinh vien--------------" << endl;
                                index = getIndexWithCode();
                                if (index == -1) {
                                    cout<< "Khong tim thay sinh vien"<< endl;
                                }else
                                {
                                    printStudent(index);
                                }
                                break;
                            case 3:
                                cout << "-------------Tim sinh vien theo ten sinh vien--------------" << endl;
                                printStudentWithName();
                                break;
                            default:
                                break;
                        }
                    } while (searchType != 0);
                }
                //Thieu tim sinh vien voi ten va ma
                break;
                
            case 4: //Them nhieu sinh vien
                int quantity;
                do
                {
                    cout << "Nhap so luong sinh vien can them: ";
                    cin >> quantity;
                    if (quantity < 0) cout << "Nhap so luong lon hon 0" << endl;
                } while (quantity < 0);
                addMultiStudent(quantity);
                break;
                
            case 5: //Them 1 sinh vien vao cuoi
                vtStudent.pushBack(getInputStudent());
                break;
                
            case 6: //Chen sinh vien
                if (vtStudent.isEmpty())
                {
                    cout << "Danh sach rong, moi them sinh vien" << endl;
                }
                else
                {
                    cout << "-------------Chen them sinh vien theo thu tu--------------" << endl;
                    int index = getIndexWithIndex();
                    vtStudent.insert(index - 1, getInputStudent());
                }
                break;
                
            case 7: //Sua sinh vien
                //Sua sinh vien voi kieu lay sinh vien theo thu tu va code
                if (vtStudent.isEmpty())
                {
                    cout << "Danh sach rong, moi nhap sinh vien!" << endl;
                }else
                {
                    cout << "--------------------------------" << endl;
                    cout << "0.Nhan phim 0 de thoat chuc nang" << endl;
                    cout << "1.Nhan phim 1 tim kiem theo vi tri" << endl;
                    cout << "2.Nhan phim 2 tim kiem theo ma sinh vien" << endl;
                    cout << "--------------------------------" << endl;
                    int index;
                    int updateType;
                    do {
                        cout<<"Nhap kieu chon sinh vien: ";
                        cin>>updateType;
                        switch (updateType) {
                            case 1:
                                index = getIndexWithIndex();
                                updateStudent(index);
                                break;
                            case 2:
                                index = getIndexWithCode();
                                if (index != -1)
                                {
                                    updateStudent(index);
                                }else
                                {
                                    cout<<"Khong tim thay sinh vien!"<< endl;
                                }
                                break;
                            default:
                                break;
                        }
                    } while (updateType != 0);
                }
                break;
                
            case 8: //Xoa sinh vien cuoi danh sach
                if (vtStudent.isEmpty())
                {
                    cout << "Danh sach khong co sinh vien!" << endl;
                }
                else
                {
                    vtStudent.popBack();
                    cout << "Da xoa sinh vien cuoi danh sach!" << endl;
                }
                break;
                
            case 9: //Xoa sinh vien thu i
                if (vtStudent.isEmpty())
                {
                    cout << "Danh sach khong co sinh vien!" << endl;
                }
                else
                {
                    int index = getIndexWithIndex();
                    vtStudent.erase(index - 1);
                    cout << "Da xoa sinh vien thu " << index - 1 << "!" << endl;
                }
                break;
                
            case 10:// In tat ca sinh vien
                printAllStudent();
                break;
                
            case 11:// Xem dung luong va kich thuoc
                cout << "Kich thuoc la " << vtStudent.getSize() << endl;
                cout << "Dung luong la " << vtStudent.getCapacity() << endl;
                break;
                
            default:
                break;
        }
    } while (option != 0);
    
    return 0;
}
