import socket

def fetch_data(group_id, server_address="172.20.241.9", port=20000, output_file="vastaanotetut_datat.txt"):
    """
    Fetches data from a TCP server using a given group ID and saves it to a file.
    
    :param group_id: The group ID to send (integer between 1 and 999).
    :param server_address: The IP address of the server.
    :param port: The TCP port of the server.
    :param output_file: The file to save the received data.
    """
    try:
        # Create a TCP socket
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
            # Connect to the server
            client_socket.connect((server_address, port))
            print(f"Connected to {server_address}:{port}")
            
            # Send the group ID followed by a newline
            message = f"{group_id}\n"
            client_socket.sendall(message.encode('utf-8'))
            print(f"Sent group ID: {group_id}")
            
            # Receive the data from the server
            received_data = b""
            while True:
                chunk = client_socket.recv(1024)  # Read in chunks of 1024 bytes
                if not chunk:  # No more data, break the loop
                    break
                received_data += chunk
            
            # Decode received data
            received_text = received_data.decode('utf-8')
            print("Data received from the server.")
            
            # Write data to the output file
            with open(output_file, "w", encoding="utf-8") as file:
                file.write(received_text)
            print(f"Data written to {output_file}")
    
    except Exception as e:
        print(f"An error occurred: {e}")

# Replace this with your actual group ID
if __name__ == "__main__":
    group_id = 123  # Replace with your actual group ID (1-999)
    fetch_data(group_id)