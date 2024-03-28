- `data`：数据位置
    - `saveings`：存档保存位置
    - `scripts`：剧情文案
    - `monsters`： 怪物数据
    - （Optional）`skills`：技能、增益
    - `maps`：地图数据
- `src`：源代码位置
    - `maze`：地图相关
        > `void showMaze()`：打印地图
        > `void loadMaze()`：从存档加载信息
        > `void saveMaze()`：保存为存档
    - `character`：主角、怪物
    - `battle`：战斗机制相关
    - `ui`：启动界面的 UI
- `README.md`