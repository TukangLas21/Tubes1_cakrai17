# Milestone 1 Tugas Besar Ca-KRAI
> Magang Ca-KRAI 17 Divisi Kontrol

## Dependencies
Program ini membutuhkan [GNU Compiler](https://sourceforge.net/projects/mingw/) untuk mengompilasi program dalam C++ ini.

## Memulai
Untuk menjalankan program, silakan klon repository terlebih dahulu.
```sh
git clone https://github.com/TukangLas21/Tubes1_cakrai17.git
cd Tubes1_cakrai17
```

Lalu, compile dan jalankan program dengan perintah berikut ini.
```sh
g++ -o run main.cpp fsm.cpp
./run
```

## Penjelasan Implementasi
Program ini mengimplementasi header file `fsm.hpp` yang berisi kelas FSM yang memiliki berbagai metode dan atribut. Implementasi program mengikuti konsep OOP dan penjelasan kerja masing-masing metode berupa komentar. Berikut penjelasan yang lebih detail pada setiap metode/fungsi:
- Fungsi `millis()`: Mengembalikan waktu saat ini dalam milliseconds berbentuk unsigned 32-bit integer. 
- Konstruktor `FSM()`: Konstruktor default yang menginisialisasi sebuah objek FSM dengan atribut-atributnya bernilai 0. Diinisalisasi juga sebuah vector `stateHistory`.
- Konstruktor terdefinisi `FSM(uint32_t delay)`: Konstruktor yang menginisialisasi sebuah objek FSM dengan nilai atribut `delay` yang ditentukan. Konstruktor ini memanggil konstruktor default sebelumnya dengan menambahkan inisialisasi atribut `delay` dengan nilai yang diinginkan.
- Destruktor `~FSM()`: Destruktor yang akan membersihkan atribut-atribut objek. Karena kelas FSM tidak memiliki atribut yang perlu alokasi memori manual, destruktor hanya memanggil metode clean untuk membersihkan isi vector `stateHistory`.
- `getCurrentState()`: Mengembalikan atribut `currentState`.
- `transitionToState(SystemState newState)`: Mengubah atribut `currentState` menjadi `newState` dan mengubah atribut `lastHeartbeat` menjadi waktu saat ini dalam milliseconds dengan memanggil fungsi `millis()`.
- `setDelay(uint32_t delay)`: Mengubah nilai atribut `delay` dengan nilai parameter.
- `getDelay(uint32_t &delay)`: Mengubah nilai parameter dengan nilai atribut `delay` (passing by reference).
- `setErrorCount(int count)`: Mengubah nilai atribut `errorCount` dengan nilai parameter.
- `getErrorCount()`: Mengembalikan nilai atribut `errorCount`.
- `setMoveCount(int count)`: Mengubah nilai atribut `moveCount` dengan nilai parameter.
- `getMoveCount()`: Mengembalikan nilai atribut `moveCount`.
- `addStateToHistory(SystemState state, uint32_t time)`: Menambahkan sebuah pair SystemState dan waktu ke dalam vector `stateHistory`. Metode ini menggunakan metode vector berupa `emplace_back()` agar dapat langsung mengonstruksi objek pair dan memasukkan pair tersebut ke dalam vector.
- `getStateHistory()`: Mengembalikan vector `stateHistory`.
- `getLastHeartbeat()`: Mengembalikan nilai atribut `lastHeartbeat`.
- `setLastHeartbeat(uint32_t time)`: Mengubah nilai atribut `lastHeartbeat` dengan nilai parameter.
- `start()`: Membuat sebuah loop yang selalu memanggil metode `update()` dengan interval 1000 milliseconds. Loop akan berhenti jika atribut `currentState` bernilai STOPPED. Jika loop dihentikan, fungsi `update()` akan dipanggil sekali lagi untuk memastikan state STOPPED diproses.
- `update()`: Metode yang memanggil fungsi berdasarkan `currentState` objek. Setelah memanggil fungsi tersebut, atribut `lastHeartbeat` akan di-update dengan waktu saat ini menggunakan fungsi `millis()` dan menambahkan state beserta waktu pada vector `stateHistory`.
- `printStatus()`: Metode yang print status atribut objek saat ini, meliputi atribut `currentState`, `lastHeartbeat`, `delay`, dan `errorCount`, ke terminal.
- `printStateHistory()`: Metode yang print riwayat state pada vector `stateHistory` dengan mengiterasi setiap elemen pada vector, kemudian print elemen tersebut.
- `performProcess()`: Metode yang dijalankan pada state IDLE. Metode ini akan meminta pengguna untuk memilih proses yang akan dilaksanakan dengan memasukkan nilai 1-4. Jika pengguna memilih 1 (IDLE), metode akan memanggil fungsi `printStatus()` dan `printStateHistory()` serta meng-update atribut `currentState`. Memasukkan nilai 2, 3, atay 4 akan mengubah `currentState` menjadi MOVEMENT, SHOOTING, atau CALCULATION secara berurutan.
- `performMovement()`: Metode yang dipanggil pada state MOVEMENT. Melakukan print pesan, lalu meng-increment atribut `moveCount`. Jika atribut tersebut bernilai 3 atau lebih, state akan dipindah menjadi SHOOTING dan `lastHeartbeat` di-update dengan waktu saat ini.
- `performShooting()`: Metode yang dipanggil pada state SHOOTING. Melakukan print pesan, lalu me-reset atribut `moveCount` kembali ke 0. State diubah menjadi IDLE dan `lastHeartbeat` di-update dengan waktu saat ini.
- `performCalculation()`: Metode yang dipanggil pada state CALCULATION. Melakukan print pesan, lalu mengecek nilai atribut `moveCount`. Jika nilai atribut tersebut 0, state dipindah ke state ERROR, jika tidak, maka state diubah menjadi IDLE.
- `performErrorHandling()`: Metode yang dipanggil pada state ERROR. Melakukan print pesan, lalu meng-increment nilai atribut `errorCount`. Jika nilai atribut tersebut melebihi 3, maka state pindah ke STOPPED. Jika tidak, state diubah menjadi IDLE.
- `shutdown()`: Metode yang dipanggil pada state STOPPED. Melakukan print pesan, lalu menghapus isi vector `stateHistory` dengan memanggil metode `clear()` dan meng-update atribut `lastHeartbeat` dengan waktu saat ini.

## Author
Aria Judhistira - 13523112
