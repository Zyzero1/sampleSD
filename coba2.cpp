#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct Node {
    string kode;
    string nama_sekolah;
    string telepon;
    int jumlah_siswa;
    Node* next;
};

Node* createNode(string kode, string nama_sekolah, string telepon, int jumlah_siswa) {
    Node* newNode = new Node;
    newNode->kode = kode;
    newNode->nama_sekolah = nama_sekolah;
    newNode->telepon = telepon;
    newNode->jumlah_siswa = jumlah_siswa;
    newNode->next = NULL;
    return newNode;
}

Node* addAndSave(Node* head, string kode, string nama_sekolah, string telepon, int jumlah_siswa, const char* filename) {
    Node* newNode = createNode(kode, nama_sekolah, telepon, jumlah_siswa);
    newNode->next = head;

    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        delete newNode;
        return head;
    }

    file << kode << "," << nama_sekolah << "," << telepon << "," << jumlah_siswa << "\n";
    file.close();

    cout << "Data ditambahkan dan disimpan ke " << filename << endl;
    return newNode;
}

void searchNode(Node* head, string kode) {
    Node* current = head;
    while (current != NULL) {
        if (current->kode == kode) {
            cout << "Data dengan kode " << kode << " ditemukan dalam daftar." << endl;
            cout << "Nama Sekolah: " << current->nama_sekolah << "\nTelepon: " << current->telepon << "\nJumlah Siswa: " << current->jumlah_siswa << endl;
            return;
        }
        current = current->next;
    }
    cout << "Data dengan kode " << kode << " tidak ditemukan dalam daftar." << endl;
}

void sortList(Node*& head) {
    if (head == NULL || head->next == NULL) {
        return; // Tidak perlu diurutkan jika 0 atau 1 elemen
    }

    Node* sortedList = NULL;

    while (head != NULL) {
        Node* current = head;
        head = head->next;

        if (sortedList == NULL || current->kode < sortedList->kode) {
            current->next = sortedList;
            sortedList = current;
        } else {
            Node* temp = sortedList;
            while (temp->next != NULL && temp->next->kode < current->kode) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }

    head = sortedList;
}

void printList(Node* head) {
    while (head != NULL) {
        cout << "Kode: " << head->kode << "\nNama Sekolah: " << head->nama_sekolah << "\nTelepon: " << head->telepon << "\nJumlah Siswa: " << head->jumlah_siswa << endl << endl;
        head = head->next;
    }
}

void displayAll(Node* head) {
    if (head == NULL) {
        cout << "Tidak ada data sekolah untuk ditampilkan." << endl;
        return;
    }

    cout << "Semua Data Sekolah:" << endl;
    printList(head);
}

int main() {
    Node* head = NULL;

    string kode, nama_sekolah, telepon;
    int jumlah_siswa;
    int choice;

    do {
        cout << "\n1. Tambah Data Sekolah\n2. Cari Data Sekolah\n3. Urutkan Data Sekolah\n4. Tampilkan Semua Data Sekolah\n0. Keluar\n";
        cout << "Masukkan pilihan Anda: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Masukkan kode sekolah: ";
                cin >> kode;
                cout << "Masukkan nama sekolah: ";
                cin.ignore(); // Untuk mengonsumsi karakter newline yang ditinggalkan oleh cin sebelumnya
                getline(cin, nama_sekolah);
                cout << "Masukkan telepon: ";
                cin >> telepon;
                cout << "Masukkan jumlah siswa: ";
                cin >> jumlah_siswa;
                head = addAndSave(head, kode, nama_sekolah, telepon, jumlah_siswa, "data.csv");
                break;
            case 2:
                cout << "Masukkan kode sekolah untuk dicari: ";
                cin >> kode;
                searchNode(head, kode);
                break;
            case 3:
                sortList(head);
                cout << "\nData Sekolah Setelah Diurutkan:" << endl;
                printList(head);
                break;
            case 4:
                displayAll(head);
                break;
            case 0:
                cout << "Selamat tinggal!\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (choice != 0);

    return 0;
}

