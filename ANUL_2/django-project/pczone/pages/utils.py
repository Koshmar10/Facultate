from datetime import datetime
from urllib.parse import urlparse

class Accesare:
    _next_id = 1
    
    def __init__(self, ip_client=None, url=None, data=None):
        self.id = Accesare._next_id
        Accesare._next_id += 1
        self.ip_client = ip_client
        self.url = url
        self.data = data or datetime.now()
    
    def lista_parametri(self):
        return [
            ("id", self.id),
            ("ip_client", self.ip_client),
            ("url", self.url),
            ("data", self.data),
        ]
    def get_url(self):
        return self.url
    def get_data(self, format_str="%Y-%m-%d %H:%M:%S"):
        return self.data.strftime(format_str)  
    def pagina(self):
        return urlparse(self.url).path
def afis_data(data_type):
    now = datetime.now() 
    weekday_names = ["luni", "marți", "miercuri", "joi", "vineri", "sâmbătă", "duminică"]
    month_names = [
        "ianuarie", "februarie", "martie", "aprilie", "mai", "iunie",
        "iulie", "august", "septembrie", "octombrie", "noiembrie", "decembrie"
    ]

    formatted_zi = f"{weekday_names[now.weekday()]}, {now.day} {month_names[now.month - 1]} {now.year} "
    formatted_timp = now.strftime("%H:%M")
    if data_type == "zi":
        return formatted_zi
    if data_type == "timp":
        return formatted_timp
    return ""

def get_client_ip(request):
    ip = request.META.get('REMOTE_ADDR')
    return ip

accesari = []