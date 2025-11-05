# uiaccess-demo
Missing UIAccess on Windows 11 24H2 when started using short path names.

1. Build `uitest.exe`.
2. Sign `uitest.exe`.
3. Create a new folder in the `C:\Program Files` folder. Copy `uitest.exe` into the newly created folder.
4. Run Process Explorer. Right click the columns header and select Select Columns. Add the Integrity Level and UI Access columns.

5. Open an elevated command prompt and run: `"C:\Program Files\uitest\uitest.exe"`. Output:
```
integrity level: 3000
ui access: 1
```
Process Explorer shows "UI Access" in the "UI Access" column.

7. Open a command prompt and run: `"C:\PROGRA~1\uitest\uitest.exe"`. Output:
```
integrity level: 3000
ui access: 0
```
Process Explorer shows nothing in the "UI Access" column.
