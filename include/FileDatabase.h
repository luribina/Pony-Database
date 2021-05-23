
#ifndef LAB2_FILEDATABASE_H
#define LAB2_FILEDATABASE_H

#include <map>
#include <set>
#include <vector>
#include <fstream>

#include "CSVParser.h"
#include "Pony.h"

class FileDatabase {
public:

    FileDatabase() = default;

    ~FileDatabase() = default;

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

    bool is_end() const;

    void reset_state();

private:
    CSVParser csvParser;
    unsigned long next_id;
    std::set<unsigned long> deleted_items;
    std::map<unsigned long, Pony> updated_items;
    std::vector<Pony> created_items;
    bool all_state;
    bool request_end;

    void save_changes();

    void save_to_file(std::ofstream &file);

    bool check_file();

    std::vector<Pony> read_next();

};


#endif //LAB2_FILEDATABASE_H
