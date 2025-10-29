# middleware.py
from .utils import Accesare, accesari, get_client_ip



class LogMiddleware:
    def __init__(self, get_response):
        self.get_response = get_response

    def __call__(self, request):
        # 🔹 Creăm obiectul Accesare înainte de a procesa răspunsul,
        # ca să logăm inclusiv pagina /log.
        accesari.append(
            Accesare(
                ip_client=get_client_ip(request),
                url=request.build_absolute_uri()
            )
        )

        # continuăm fluxul normal
        response = self.get_response(request)
        return response
