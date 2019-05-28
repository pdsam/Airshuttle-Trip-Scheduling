import sys
import os
import random

if len(sys.argv) != 3:
	print("Usage: python {0} <location> <number of reservations>".format(sys.argv[0]))

location = sys.argv[1]
n_res = sys.argv[2]

# Read available nodes for that location
nodes_list = []
nodes_filename = "../maps/" + location + "/" + "T06_nodes_X_Y_" + location + ".txt"
with open(nodes_filename, "r") as f:
	f.readline()
	nodes_list = [line.rstrip('\n')[1:].split(',')[0] for line in f]

# List of names
names_list = ["Son","Man","Brandon","Fidel","Jc","Fabian","Dannie","Jerald","Hal","Doug","Maynard","Santos","Rigoberto","Franklyn","Howard","Dorian","Edgardo","Rogelio","Everette","Nicolas","Johnie","Jeffery","Carlos","Mickey","Moises","Brooks","Jay","Sean","Antony","Scottie","Felton","Alejandro","Antonia","Rudy","Nathanael","Rayford","Curt","Delmar","William","Denis","Anton","Antone","Osvaldo","Isaac","Freeman","Morton","Manuel","Samual","Sterling","Lewis","Liane","Alane","Rima","Magnolia","Valencia","An","Vicenta","Margene","Gia","Shery","Saran","Madge","Raeann","Buffy","Thalia","Hulda","Yuki","Lita","Venice","Easter","Sonya","Delois","Cleora","Sharri","Genie","Kyung","Petronila","Veta","Shawana","Adelia","Karine","Agnus","Inell","Ashton","Marian","Henriette","Cecelia","Tula","Arlean","Valarie","Talitha","Solange","Ila","Sara","Marline","Alexandria","Gaynelle","Patria","Jaclyn","Shauna","Josue","Yuk","Evette","Awilda","Berry","Linette","Ralph","Nathalie","Antony","Darci","Rhiannon","Rigoberto","Chrystal","Clarence","Clora","Genny","Renea","Maryam","Justine","Nada","Denisse","Matilda","Johnnie","Julee","Harriette","Carolann","Sharell","Bradley","Olinda","Leana","Belva","Jamila","Anna","Liane","Flavia","Deangelo","Loriann","Georgette","Latisha","Elias","Danita","Deborah","Shirlene","Simone","Alissa","Eleonor","Ethan","Elisabeth","Carrie","Debi","Louann","Carli","Collin","Scott","Hubert","Arcelia","Janell","Neal","Ida","Jazmine","Liberty","Geraldine","Greg","Clifford","Edna","Klara","Janae","Aisha","Laraine","Earnestine","Christinia","Ebonie","Gerardo","Genaro","Luis","Marcene","Hoa","Marg","Era","Virgie","Karri","Gilberte","Floria","Eda","Emilio","Jesica","Creola","Isadora","Logan","Moira","Kenda","Angelia","Theodora","Molly","Alpha","Rupert","Tod","Sherley","Chadwick","Na"]

output_filename = "" + location + "/reservations_" +n_res  + ".txt"
while os.path.isfile(output_filename):
	output_filename = "/" + location + "/reservations_" + random.choice(nodes_list) + ".txt"

# write reservations in format: name NIF node hour minute second passengers
os.makedirs(os.path.dirname(output_filename), exist_ok=True)
with open(output_filename, "w") as f:
	f.write(n_res + '\n')
	for i in range(int(n_res)):
		name = random.choice(names_list)
		nif = str(random.randint(1,9)) + ''.join(["%s" % random.randint(0,9) for num in range(0, 8)])
		node = random.choice(nodes_list)
		hour = str(random.randint(0, 23)).zfill(2)
		minute = str(random.randint(0, 59)).zfill(2)
		second = str(random.randint(0, 59)).zfill(2)
		passengers = str(random.randint(1,10))
		reservation = name + " " + nif + " " + node + " " + hour + " " + minute + " " + second + " " + passengers + "\n"
		f.write(reservation)