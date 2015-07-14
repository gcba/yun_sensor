import api, sys
REMOTE_SERVER = "www.google.com.ar"

def is_connected():
  try:
    host = socket.gethostbyname(REMOTE_SERVER)
    s = socket.create_connection((host, 80), 2)
    return True
  except:
  	print "NO-INTERNET"	
  return False

def main():
	if not sys.argv:
		print "NO-ARGS"
	else:
		data ={
		'id1'		: sys.argv[1],
		'datatype1' : 9001,
		'data1'		:sys.argv[2],
		'id2'		: sys.argv[1],
		'datatype2' : 9002,
		'data2'		:sys.argv[3],
		'id3'		: sys.argv[1],
		'datatype3' : 9003,
		'data3'		:sys.argv[4],
		}
		try:
			response = api.Data.dynamic_create(data)
			print "PUSH-OK"
		except Exception as e:
			print "FALLO-API"
		with open("data.csv", "a") as myfile:
			myfile.write("%s , %s , %s \n" % (sys.argv[2],sys.argv[3],sys.argv[4]))
		myfile.close()
				

			

if __name__ == '__main__':
	main()