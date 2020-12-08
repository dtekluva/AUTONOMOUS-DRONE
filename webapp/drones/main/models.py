from django.db import models

# Create your models here.

class Trigger(models.Model):
    name = models.CharField(null=True, blank=True, max_length=100)
    code = models.CharField(null=True, blank=True, max_length=100)
    is_triggered = models.BooleanField(default=False)