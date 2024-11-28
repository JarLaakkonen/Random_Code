import socket

def fetch_data_and_save(group_id, output_file):
    server_address = ('172.20.241.9', 20000)

    # Luo TCP-socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        try:
            # Yhdistä palvelimeen
            client_socket.connect(server_address)
            print(f"Yhdistetty palvelimeen {server_address}")

            # Lähetä groupid ja rivinvaihto
            client_socket.sendall(f"{group_id}\\n".encode('utf-8'))

            # Vastaanota data
            received_data = b""
            while True:
                chunk = client_socket.recv(4096)  # Lue data 4096 tavun paloissa
                if not chunk:  # Ei enää dataa
                    break
                received_data += chunk

            # Tallenna tiedostoon
            with open(output_file, 'wb') as file:
                file.write(received_data)

            print(f"Data tallennettu tiedostoon: {output_file}")

        except Exception as e:
            print(f"Virhe: {e}")

if __name__ == "__main__":
    import sys

    if len(sys.argv) != 3:
        print("Käyttö: python tcp_socket_client.py <group_id> <output_file>")
    else:
        group_id = sys.argv[1]
        output_file = sys.argv[2]
        fetch_data_and_save(group_id, output_file)
