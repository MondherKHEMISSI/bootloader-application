import matplotlib.pyplot as plt
import struct

def parse_binary_file(file_path):
    # Open the binary file in binary read mode
    with open(file_path, 'rb') as file:
        # Read the content of the file
        binary_data = file.read()

        # Example parsing: reading byte by byte
        record_size = 16  # Total size of each record in bytes
        num_records = len(binary_data) // record_size

        # Print the header
        print("Record  | TimeStamp     | Module ID | Event ID | Data Size |        Data        | Priority")
        print("-" * 94)  # Separator line


          # Initialize counters for module ID 7 and module ID 5
        module_7_count = 0
        module_5_count = 0

        # Lists to store timestamp and corresponding counts
        timestamps = []
        module_7_counts = []
        module_5_counts = []

        # Iterate through the binary data
        for i in range(num_records):
            # Extract the data for each record
            record_start = i * record_size
            record = binary_data[record_start:record_start + record_size]


            
            # Extract the individual fields from the record
            timestamp = record[:4]
            module_id = record[4]
            event_id = record[5]
            data_size = record[6]
            data = record[8:12]
            priority = record[12:]

            # Print the formatted record
            print(f"{i + 1:<7}| {' '.join(f'{byte:02X}' for byte in timestamp):13} | {module_id:9} | {event_id:9} | {data_size:9} | {' '.join(f'{byte:02X}' for byte in data):18} | {' '.join(f'{byte:02X}' for byte in priority)}")

             # Update counters based on module ID
            if module_id == 7:
                module_7_count += 1
            elif module_id == 5:
                module_5_count += 1

            # Append timestamp and corresponding counts
            timestamps.append(struct.unpack('<I', timestamp)[0] / 60000)  # Unpack timestamp as unsigned integer
            module_7_counts.append(module_7_count)
            module_5_counts.append(module_5_count)

            print()  # Empty line for readability

         # Plot the counts over time
        plt.plot(timestamps, module_7_counts, label='Module ID 7')
        plt.plot(timestamps, module_5_counts, label='Module ID 5')
        plt.xlabel('Time (minutes)')
        plt.ylabel('Count')
        plt.title('Module ID 7 and Module ID 5 Counts Over Time')
        plt.legend()
        plt.show()
# Appel de la fonction avec le chemin vers le fichier binaire
parse_binary_file('/home/mondher/bootloader-application/memoryTest.bin')
