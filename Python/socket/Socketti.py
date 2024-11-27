import socket


server_address = ('172.20.241.9', 20000)
group_id = b'999'  # Ryhmänumero, joka lähetetään palvelimelle
output_file = "vastaanotetut_datat.txt"  # Tiedosto tallennusta varten

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
 
    s.connect(server_address)
    print(f"Connected to {server_address}")
    
   
    s.sendall(group_id)
    
   
    with open(output_file, 'w', encoding='utf-8') as f:
        while True:
           
            data = s.recv(1024)
            if len(data) == 0:
                print(f"No data coming whyy")
                break
            
            f.write(data.decode('utf-8'))
            
            print(data.decode('utf-8'), end='')

print(f"\nData saved to {output_file}")
