# Если нужно скомпилировать

библиотеку типов необходимо зарегистрировать для использования методов
в консоли разработчика перейдите в папку <путь к репозиторию>/ьуьфддщс/exLibs и выполните команду regasm MessageGUI.dll /tlb:MessageGUI.tlb
при импорте путь укзаан относительный, всё должно пройти нормально. Для того, чтобы программа получила доступ к памяти, и для запуска нескольких клиентов нужно скомпилить код, потом запускать полученный .exe от имени администратора
