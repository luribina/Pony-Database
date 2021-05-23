Simple Database
---

### Installation

1. Clone repository
2. `cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=[Debug|Release|Sanitized] [path/to/source]`
3. `make`
4. `cd app`
5. `./database`

### Available commands

- **[m]** - Print menu
- **[o]** - Open DB
- **[c]** - Close DB
- **[l]** - List all objects
- **[i]** - Find by ID
- **[t]** - Find by type
- **[r]** - Remove by ID
- **[n]** - Create new object
- **[u]** - Update object
- **[q]** - Quit

## Application description

There are three main parts - object description, user interface, file handling(parser + database)


### Saved object

Class *[`Pony`](include/Pony.h)*

Class members

```
id - unique key unsigned long
name - string
age - unsigned int 
height - double
type - enum class [Unicorn|Pegasus|Earthpony|Alicorn]
```

### User Interface

Class *[`Interface`](include/Interface.h)*

Contains methods for reading and outputting strings

```cpp
std::string read_line();
void write_line(std::string &&line);
```

Methods for reading object parameters

```cpp
unsigned long read_id();
unsigned int read_age();
double read_height();
Pony::Type read_type();
std::string read_name();
Pony read_object();
```

### File Handling

In order to save information about objects, the CSV file format was chosen as it is simple enough for parsing files without using other libraries.

#### Parser
A simple CSV parser using templates was written, which can be used with any csv file.
You can check it [here](https://github.com/luribina/CSV-Parser). (description + usage example)


#### Database

Class [`FileDatabase`](include/FileDatabase.h)

Available methods

```cpp
bool open_db(std::string &&name);
void close_db();
bool is_open();
bool id_exists(unsigned long seek_id);
Pony read_by_id(unsigned long seek_id);
bool delete_by_id(unsigned long delete_id);
void update_by_id(Pony &&pony);
void create_object(Pony &&pony);
std::vector<Pony> find_by_type(Pony::Type seek_type);
std::vector<Pony> list_all_objects();
```

## :3

If you've read to the end, here have cat with bread hat

<img src="breadcat.jpg" width="400" height="400"  alt="breadcat"/>
