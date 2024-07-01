import multiprocessing
import numpy as np
from multiprocessing import shared_memory, Process, Lock

def worker(shared_memory_name, array_shape, lock, process_id):
    with lock:
        existing_shm = shared_memory.SharedMemory(name=shared_memory_name)
        shared_number = np.ndarray((1,), dtype=np.int64, buffer=existing_shm.buf[:8])[0]
        shared_array = np.ndarray(array_shape, dtype=np.float64, buffer=existing_shm.buf[8:])
        print(f"Process {process_id} - Original data: shared_number={shared_number}, shared_array={shared_array}")
        
        shared_number += process_id
        shared_array += process_id
        
        np.ndarray((1,), dtype=np.int64, buffer=existing_shm.buf[:8])[0] = shared_number
        np.copyto(np.ndarray(array_shape, dtype=np.float64, buffer=existing_shm.buf[8:]), shared_array)
        
        existing_shm.close()

if __name__ == "__main__":
    shared_number = np.array([42], dtype=np.int64)
    shared_array = np.array([1.0, 2.0, 3.0, 4.0, 5.0], dtype=np.float64)
    
    total_size = shared_number.nbytes + shared_array.nbytes
    shm = shared_memory.SharedMemory(create=True, size=total_size)
    
    np.ndarray((1,), dtype=shared_number.dtype, buffer=shm.buf[:8])[:] = shared_number
    np.ndarray(shared_array.shape, dtype=shared_array.dtype, buffer=shm.buf[8:])[:] = shared_array
    
    lock = Lock()
    print(f"Main process - Original data: shared_number={shared_number[0]}, shared_array={shared_array}")
    
    processes = []
    for i in range(1, 4):  
        p = Process(target=worker, args=(shm.name, shared_array.shape, lock, i))
        processes.append(p)
        p.start()
    
    for p in processes:
        p.join()
    
    final_shared_number = np.ndarray((1,), dtype=np.int64, buffer=shm.buf[:8])[0]
    final_shared_array = np.ndarray(shared_array.shape, dtype=np.float64, buffer=shm.buf[8:])
    
    print(f"Main process - Modified data: shared_number={final_shared_number}, shared_array={final_shared_array}")
    
    shm.close()
    shm.unlink()
