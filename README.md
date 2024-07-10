<div directon='right' style="text-align: right">

# מבנה נתונים עץ עם אפשרויות מעבר מרובות

פרויקט זה מיישם מבנה נתונים של עץ ב-C++ עם שיטות מעבר שונות וממשק גרפי להצגת העץ באמצעות SDL2 ו-SDL2_ttf.

## מטרה

מטרת הפרויקט היא להדגיש את היכולות המתקדמות של C++, כולל:

- **טמפלייטים**: האפשרות לאחסן נתונים של כל סוג בעץ.
- **איטרטורים**: איטרטורים מותאמים אישית לשיטות שונות לעבור בעץ.
- **מבני נתונים**: ביצוע של צמתי עץ ואלגוריתמים לעבור בהם.
- **פונקציות של הספרייה התקנית**: שימוש ברכיבים מ-STL כמו `stack`, `queue`, ו־`priority_queue`.

## קבצים

1. **Tree.hpp** - מכיל את מחלקת `Tree` עם מספר שיטות לעבור בעץ.
2. **TreeGUI.hpp** - מכיל את מחלקת `TreeGUI` להצגת העץ.
3. **Node.hpp** - מכיל את מחלקת `Node` המייצגת כל צומת בעץ.

## תכונות

- **שיטות מעבר בעץ**:
  - PreOrder
  - PostOrder
  - InOrder
  - BFS (חיפוש לרוחב)
  - DFS (חיפוש לעומק)
  - Heap

- **הצגה גרפית**:
  - ציור העץ באמצעות SDL2
  - הצגת ערכי הצמתים באמצעות SDL2_ttf

## תלותים

- SDL2
- SDL2_ttf

## התקנה

### לינוקס

1. התקן את SDL2 ו־SDL2_ttf:
    ```sh
    sudo apt-get install libsdl2-dev libsdl2-ttf-dev
    ```

2. שיבט את מאגר הפרויקט:
    ```sh
    git clone https://github.com/yourusername/yourproject.git
    cd yourproject
    ```

3. בנה את הפרויקט:
    ```sh
    g++ -o tree main.cpp -lSDL2 -lSDL2_ttf
    ```

4. הרץ את הפרויקט:
    ```sh
    ./tree
    ```

## שימוש

### יצירת עץ

כדי ליצור עץ, השתמש במחלקות `Tree` ו־`Node`:

```cpp
#include "node.hpp"
#include "tree.hpp"

Node<int> root(1);
Node<int> child1(2);
Node<int> child2(3);

Tree<int> tree;
tree.add_root(root);
tree.add_sub_node(root, child1);
tree.add_sub_node(root, child2);
```

### עבודה עם איטרטורים

כדי לעבוד עם העץ באמצעות שיטות מעבר שונות:

```cpp
// PreOrder Traversal
for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
    cout << it->get_value() << " ";
}
cout << endl;
```

### הצגת העץ

כדי להציג את העץ, השתמש במחלקת `TreeGUI`:

```cpp
#include "treeGUI.hpp"

TreeGUI<int> gui(tree.get_root());
gui.draw();
```

## תרומה

אם ברצונך לתרום לפרויקט זה, בבקשה פתח פורק ושלח בקשת משיכה.

## רישיון

פרויקט זה מוגן ברישיון MIT - ראה קובץ ה-LICENSE לפרטים נוספים.

## יוצרים

- שמך - [yourusername](https://github.com/yourusername)

---

</div>