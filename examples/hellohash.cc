#include <iostream>
#include <string>

#include <libcuckoo/nv_cuckoohash_map.hh>
#define CLASS_ID 1
#define Type nv_cuckoohash_map<int, std::string>

PersistentObject *BaseFactory(uuid_t id) {
  ObjectAlloc *alloc = GlobalAlloc::getInstance()->newAllocator(id);
  void *temp = alloc->alloc(sizeof(Type));
  Type *obj = (Type *)temp;
  Type *object = new (obj) Type(id);
  return object;
}

PersistentObject *RecoveryFactory(NVManager *m, CatalogEntry *e) {
  return BaseFactory(e->uuid);
}

Type *Factory(uuid_t id) {
  NVManager &manager = NVManager::getInstance();
  manager.lock();
  Type *obj = (Type *)manager.findRecovered(id);
  if (obj == NULL) {
    obj = static_cast<Type *>(BaseFactory(id));
    manager.createNew(CLASS_ID, obj);
  }
  manager.unlock();
  return obj;
}

int bench_main(int argc, char **argv) {
  uuid_t uuid;
  uuid_generate(uuid);
  Type *Table = Factory(uuid);

  for (int i = 0; i < 100; i++) {
    Table->insert(i, "hello");
  }

  for (int i = 0; i < 101; i++) {
    std::string out;

    if (Table->find(i, out)) {
      std::cout << i << "  " << out << std::endl;
    } else {
      std::cout << i << "  NOT FOUND" << std::endl;
    }
  }

  return 0;
}

int main(int argc, char **argv) {
  PersistentFactory::registerFactory(CLASS_ID, RecoveryFactory);
  return Savitar_main(bench_main, argc, argv);
}
