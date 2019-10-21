# Simple demo setup for an IoT demonstration
Just a couple of electrical components and an API


## The k8s cluster
Setup like so:

```bash
gcloud beta container --project "apigee-trashcan-backends" clusters create "turnstile-demo" --region "europe-north1" --no-enable-basic-auth --cluster-version "1.13.10-gke.0" --machine-type "n1-standard-2" --image-type "COS" --disk-type "pd-standard" --disk-size "100" --scopes "https://www.googleapis.com/auth/devstorage.read_only","https://www.googleapis.com/auth/logging.write","https://www.googleapis.com/auth/monitoring","https://www.googleapis.com/auth/servicecontrol","https://www.googleapis.com/auth/service.management.readonly","https://www.googleapis.com/auth/trace.append" --num-nodes "1" --enable-cloud-logging --enable-cloud-monitoring --enable-ip-alias --network "projects/apigee-trashcan-backends/global/networks/default" --subnetwork "projects/apigee-trashcan-backends/regions/europe-north1/subnetworks/default" --default-max-pods-per-node "110" --addons HorizontalPodAutoscaling,HttpLoadBalancing --enable-autoupgrade --enable-autorepair --no-shielded-integrity-monitoring
```


## The credentials
Get the creds yo

```bash
gcloud container clusters get-credentials
```

## Add istio

## Do some app shtuff
```bash
kubectl create ns app
kubectl label namespace app istio-injection=enabled
kubectl get namespace -L istio-injection
```

## Add Apigee adapter

## Now deploy mongodb to a mongo namespace
```bash
kubectl create ns mongo
helm install --name mongo --namespace mongo \
  --set mongodbRootPassword=supersecret,mongodbUsername=aMagicUser,mongodbPassword=aMagicPass,mongodbDatabase=aMagicDB \
    stable/mongodb```
