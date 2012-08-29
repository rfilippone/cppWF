cppWF
=====

      <VirtualHost *:80>
          DocumentRoot "<path_to>/cppWF/web/public/"
          ServerName fcgi.example.net
      
          ErrorLog fcgi.example.net-error_log
          CustomLog fcgi.example.net-access_log combined
      
          <Directory "<path_to>/cppWF/web/public/">
              DirectoryIndex /fcgi/cppWF
              Options Indexes FollowSymLinks
              AllowOverride All
              Order allow,deny
              Allow from all
          </Directory>
      
          DefaultInitEnv  APPLICATION_ENV testing
      
          DefaultInitEnv  LD_LIBRARY_PATH ...add here path to needed library...
      
          Alias /fcgi/cppWF "<path_to>/cppWF/web/public/cppWF"
      
          <Location /fcgi/>
              SetHandler fcgid-script
              Options +ExecCGI
              Order deny,allow
              Allow from localhost
          </Location>
      </VirtualHost>
