# hammady.github.io

Static website generator for [hammady.github.io](http://www.hammady.net)
([www.hammady.net](http://www.hammady.net)) using
[Jekyll](https://jekyllrb.com/).

## Development

Add/Edit posts in the `_posts` folder, or change the structure if necessary in other files.

To test it locally (will take time for the first time):

    docker-compose up

Then point your browser to [http://localhost:4000](http://localhost:4000).
Note that you may change the `localhost` part if running on a remote docker host
or minikube.

### Update dependecies

The most common dependency is Jekyll itself, to update it:

    docker-compose run server bundle update jekyll github-pages

Other dependencies can be updated by changing their version in the `Gemfile`,
then issuing the upgrade command:

    docker-compose run server bundle update <gem list>

## Production

Commit and push changes, which will automatically reflect on the public website.
