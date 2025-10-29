from django.shortcuts import render
from datetime import date
from .utils import accesari, get_client_ip
from pages.utils import afis_data

# Create your views here.
def home(request):
    
    context = {"ip_client": get_client_ip(request),}
    return render(request, 'home/index.html', context)
def info(request):
    data = request.GET.get('data')
    html_sting = afis_data(data)
    context ={
        "data": html_sting
        
    }
    return render(request, 'info/index.html', context)

def log(request):
    logs = accesari
    has_error = False
    error_msg = ""
    ultimele = request.GET.get("ultimele")
    accesari_param = request.GET.get("accesari")
    iduri = request.GET.getlist("iduri")
    dubluri = bool(request.GET.get("dubluri", False))
    tabel = request.GET.get("tabel")
    param_names = request.GET.keys()
    param_count = len(param_names)
    if ultimele:
        try:
            ultimele = int(ultimele)
        except:
            has_error = True
            error_msg = "ultimele argument has bd Type"
        if ultimele > len(logs):
            has_error = True
            error_msg = f"Exista doar {len(logs)} accesari fata de {ultimele} accesari cerute"
        else:
            logs = logs[-ultimele:]
            
    if iduri:
        iduri = [int(x) for x in ",".join(iduri).split(',')]
        if not dubluri:
            iduri = set(iduri)
        print(iduri)
        new_logs = []
        for id in iduri:
            for log in logs:
                if log.id == id:
                    new_logs.append(log)
        logs = new_logs        
    num_accesari=""
    detalii_accesari = []
    if accesari_param:
        if accesari_param == "nr":
            num_accesari = len(logs)
        if accesari_param == "detalii":
            detalii_accesari = [lg.get_data("%Y-%m-%d %H:%M:%S") for lg in logs]
    as_table = False
    column = ""
    if tabel:
        if tabel == "tot":
            as_table = True
        else:
            as_table = True
            column = tabel.split(',')
    context ={
        "logs" : logs,
        "has_error": has_error,
        "error_msg": error_msg,
        "num_accesari": num_accesari,
        "detalii_accesari": detalii_accesari,
        "as_table": as_table,
        "column": column,
        "param_names": param_names,
        "param_count": param_count,
        
    }
    return render(request, 'log/index.html', context)
def about(request):
    context = {
        "ip_client": get_client_ip(request),
    }
    return render(request, 'about/index.html', context)
def cart(request):
    context ={
        "ip_client": get_client_ip(request),
    }
    return render(request, 'cart/index.html', context)
def contact(request):
    context = {
        "ip_client": get_client_ip(request),
    }
    return render(request, 'contact/index.html', context)