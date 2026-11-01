# StairGenerator

**RU** · [EN](#english)

Генератор 3D-модели лестницы с собственным программным рендером на SDL2. Количество и размер
ступенек меняются с клавиатуры, модель вращается, готовую лестницу можно сохранить в `.obj`
или загрузить триангулированную модель из `.obj`. Загружен на GitHub в декабре 2022 года.

## Управление

(сверено с `SDL_demo/UserInput.cpp`)

| Клавиша | Действие |
|---|---|
| W / S | вращение вокруг оси Z |
| A / D | вращение вокруг оси X |
| Q / E | вращение вокруг оси Y |
| Z | режим каркаса (wireframe) |
| ← / → | убрать / добавить ступеньку |
| ↑ / ↓ | изменить длину |
| F | экспорт лестницы в `.obj` (имя файла вводится в консоли, расширение добавляется само) |
| G | импорт модели из `.obj` (модель должна быть триангулированной) |
| удерживать левую кнопку мыши | перемещение изображения за курсором |
| Esc | выход |

## Стек

- C++, SDL2 (окно и вывод кадра), свой код преобразований и отрисовки
  (`graphie.cpp`, `draw.cpp`, `сoordinate_system.cpp`)
- В `SDL_demo/` лежит GLUT for Win32 3.7.6 (`glut32.dll`, `glut32.lib`)
- `brep.cpp` / `brep.h` — заготовка построения B-rep из треугольников, описана в
  [Create_brep_model](https://github.com/beanbo/Create_brep_model)
- Решение Visual Studio `labexample.sln`, проект `SDL_demo/SDL_demo.vcxproj`, toolset v142

## Сборка и запуск

1. Скачайте SDL2 2.0.4 (development libraries для Visual C++) и распакуйте в папку
   `SDL2-2.0.4` рядом с `labexample.sln` — проект ищет заголовки в
   `$(SolutionDir)\SDL2-2.0.4\include`. Путь к `SDL2.lib` при необходимости добавьте в
   настройки компоновщика.
2. Откройте `labexample.sln` в Visual Studio 2019 или новее, соберите для x86.
3. Рядом с exe должен лежать `SDL2.dll` (32-битный есть в `target_x86/` и `Debug/`).

В репозитории также лежит ранее собранный `Debug/labexample.exe`.

В этом окружении не проверялось: проект собирается только под Windows в MSVC.

## Контекст

Учебный проект по компьютерной графике (имя решения `labexample`).

---

## English

A 3D staircase generator with a hand-written software renderer on top of SDL2. The number and
size of steps change from the keyboard, the model rotates, and the stairs can be exported to
`.obj` or a triangulated `.obj` model can be imported. Uploaded to GitHub in December 2022.

**Controls:** W/S — rotate around Z, A/D — around X, Q/E — around Y, Z — wireframe,
←/→ — remove/add a step, ↑/↓ — change length, F — export to `.obj` (file name is typed in the
console, `.obj` is appended), G — import a triangulated `.obj`, hold the left mouse button — move the
picture with the cursor, Esc — quit.

**Stack:** C++, SDL2, GLUT for Win32 3.7.6 (bundled), Visual Studio solution `labexample.sln`
(toolset v142).

**Build:** put SDL2 2.0.4 development libraries for Visual C++ into `SDL2-2.0.4` next to
`labexample.sln`, open the solution in Visual Studio 2019+, build for x86, keep `SDL2.dll`
(32-bit copies are in `target_x86/` and `Debug/`) next to the executable. A prebuilt
`Debug/labexample.exe` is also committed. Not verified here: Windows and MSVC are required.

**Context:** a student computer graphics project.
